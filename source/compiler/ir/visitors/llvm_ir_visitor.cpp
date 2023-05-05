#include "core/logger.hpp"

#include "llvm_ir_visitor.hpp"
#include "ast/ast.hpp"

#include <iostream>

void LLVMIRVisitor::TranslateToIR(Program* program, std::unique_ptr<SymbolLayerTree> layer_tree,
                                  const std::filesystem::path& path) {
  LOG_TRACE("path: {}", path.native());

  this->symbol_tree = std::move(layer_tree);
  current_scope = symbol_tree->begin();
  stack.Clear();

  InitializeLLVM(path.string());

  Visit(program);
  llvm::verifyModule(*module);

  std::error_code error_code;
  llvm::raw_fd_ostream ostream(path.native(), error_code);
  module->print(ostream, nullptr);

  TerminateLLVM();
}

void LLVMIRVisitor::Visit(Program* program) {
  GenerateStandartLib();
  GenerateClassesDecl();
  GenerateMethodsDecl();
  program->main_class->Accept(this);
  Visit(program->class_declaration_list);
}

void LLVMIRVisitor::Visit(MainClass* main_class) {
  ScopeGoDown();
  LOG_DEBUG("In MainClass Declaration")

  llvm::FunctionType* function_type = llvm::FunctionType::get(
    llvm::Type::getVoidTy(*context), false
  );

  llvm::Function * main = llvm::Function::Create(
    function_type,
    llvm::Function::ExternalLinkage,
    "main",
  module
  );

  llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", main);

  builder->SetInsertPoint(entry);
  Visit(main_class->statement_list);
  builder->CreateRetVoid();

  llvm::verifyFunction(*main);

  //TODO make flag
  //pass_manager->run(*main);

  ScopeGoUp();
}

void LLVMIRVisitor::Visit(ClassDeclaration* class_declaration) {
  ScopeGoDown();

  current_class = class_declaration->class_type;
  Visit(class_declaration->declaration_list);

  ScopeGoUp();
}

void LLVMIRVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  LOG_DEBUG("In ClassRef-Declaration List")
  class_declaration_list->Accept(this);
}

void LLVMIRVisitor::Visit(DeclarationList* declaration_list) {
  LOG_DEBUG("In Declaration List")
  declaration_list->Accept(this);
}

void LLVMIRVisitor::Visit(MethodDeclaration* method) {
  ScopeGoDown();
  LOG_DEBUG("In Method Declaration")

  current_method = method->method_type;

  llvm::Function* llvm_method = module->getFunction(GenMethodName(current_class, method->method_type));
  llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", llvm_method);
  builder->SetInsertPoint(entry);

  //deal with this
  llvm::Type* type = llvm_method->getFunctionType()->getParamType(0);
  std::shared_ptr<IRObject> obj = current_scope->GetFromCurrent(Symbol("__this"));
  obj->Set(builder->CreateAlloca(type, nullptr, "__this"));
  builder->CreateStore(llvm_method->getArg(0), obj->Get());
  current_this = obj->Get();

  // alloc params on stack
  for (int arg_no = 0; arg_no < method->method_type->GetArgsNum(); ++arg_no) {
    llvm::Type* type = llvm_method->getFunctionType()->getParamType(arg_no + 1);
    std::shared_ptr<IRObject> obj = current_scope->GetFromCurrent(method->method_type->GetArg(arg_no).symbol);
    obj->Set(builder->CreateAlloca(type, nullptr, method->method_type->GetArg(arg_no).symbol.name));
    builder->CreateStore(llvm_method->getArg(arg_no + 1), obj->Get());
  }

  Visit(method->statement_list);

  stack.Pop();

  if (current_method->GetReturnType()->IsVoid()) {
    stack.Put(builder->CreateRetVoid());
  }

  llvm::verifyFunction(*llvm_method);

  //TODO add flag
  //pass_manager->run(*method);

  ScopeGoUp();
}

void LLVMIRVisitor::Visit(VariableDeclaration* declaration) {
  LOG_DEBUG("In Variable Declaration: [{}] {}", declaration->type->ToString(), declaration->identifier.name)

  //insert in the beginning for optimizer
  llvm::Function* function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock& block = function->getEntryBlock();

  llvm::IRBuilder<> tmp(&block, block.begin());

  std::shared_ptr<IRObject> obj = current_scope->GetFromCurrent(declaration->identifier);

  obj->Set(tmp.CreateAlloca(GetLLVMType(declaration->type), nullptr, declaration->identifier.name));

  stack.Put(obj->Get());
}

void LLVMIRVisitor::Visit(TrueExpression* expression) {
  LOG_DEBUG("In True Expression")

  llvm::Value* val = llvm::ConstantInt::getSigned((llvm::Type::getInt8Ty(*context)), 1);
  stack.Put(val);
}

void LLVMIRVisitor::Visit(FalseExpression* expression) {
  LOG_DEBUG("In False Expression")

  llvm::Value* val = llvm::ConstantInt::getSigned((llvm::Type::getInt8Ty(*context)), 0);
  stack.Put(val);
}

void LLVMIRVisitor::Visit(IdentifierExpression* expression) {
  LOG_DEBUG("In Identifier Expression: {}", expression->identifier.name)

  std::shared_ptr<IRObject> obj = current_scope->GetFromAnywhere(expression->identifier);

  if (obj->GetType()->IsClass()) {
    last_expr_class = std::reinterpret_pointer_cast<ClassType>(obj->GetType());
  }

  llvm::Value* ptr_val = nullptr;

  if (obj->IsLocal()) {
    ptr_val = obj->Get();
  } else if (obj->IsField()) {
    ptr_val = builder->CreateGEP(
    module->getTypeByName(current_class->GetName().name),
      builder->CreateLoad(GetLLVMType(current_class), current_this),
      llvm::ArrayRef<llvm::Value*>(
        {
          llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), 0),
          llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)),
                                       symbol_tree->GetClassTable()->GetInfo(current_class).GetFieldNo(expression->identifier))}
      )
    );
  }

  stack.Put(builder->CreateLoad(GetLLVMType(obj->GetType()), ptr_val));
}

void LLVMIRVisitor::Visit(IntegerExpression* expression) {
  LOG_DEBUG("In Integer Expression: {}", expression->value)

  llvm::Value* val = llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), expression->value);
  stack.Put(val);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
  LOG_DEBUG("In Not Expression")

  llvm::Value* val = Accept(expression->expression);
  stack.Put(builder->CreateNot(val, "not"));
}

void LLVMIRVisitor::Visit(AssignmentStatement* statement) {
  LOG_DEBUG("In Assignment Statement")
  stack.Pop();

  //var == ptr to var
  llvm::Value* var = Accept(statement->value);
  llvm::Value* expr = Accept(statement->expression);

  stack.Put(builder->CreateStore(CreateCast(expr, var->getType()->getPointerElementType()), var));
}

void LLVMIRVisitor::Visit(IfElseStatement* statement) {
  LOG_DEBUG("In IfElse Statement")
  stack.Pop();

  llvm::Value* cond_expr = CreateCast(Accept(statement->cond_expression), builder->getInt8Ty());

  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_expr, builder->getInt1Ty(), true);

  llvm::Value* cmp = builder->CreateICmpEQ(bool_cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* then_block = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cmp, then_block, else_block);

  builder->SetInsertPoint(then_block);

  ScopeGoDown();
  Visit(statement->statement_true);
  ScopeGoUp();

  stack.Pop();

  builder->CreateBr(merge_block);

  function->getBasicBlockList().push_back(else_block);
  builder->SetInsertPoint(else_block);

  ScopeGoDown();
  Visit(statement->statement_false);
  ScopeGoUp();

  stack.Pop();

  builder->CreateBr(merge_block);

  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);

  stack.Put(merge_block);
}

void LLVMIRVisitor::Visit(IfStatement* statement) {
  LOG_DEBUG("In If Statement")
  stack.Pop();

  llvm::Value* cond_expr = CreateCast(Accept(statement->cond_expression), builder->getInt8Ty());

  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_expr, builder->getInt1Ty(), true);
  llvm::Value* cmp = builder->CreateICmpEQ(bool_cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* then_block = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cmp, then_block, else_block);

  builder->SetInsertPoint(then_block);

  ScopeGoDown();
  Visit(statement->statement_true);
  ScopeGoUp();

  stack.Pop();
  builder->CreateBr(merge_block);

  function->getBasicBlockList().push_back(else_block);
  builder->SetInsertPoint(else_block);
  builder->CreateBr(merge_block);

  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);

  stack.Put(merge_block);
}

void LLVMIRVisitor::Visit(PrintStatement* statement) {
  LOG_DEBUG("In Print Statement")
  stack.Pop();

  llvm::Value* value = Accept(statement->expression);

  std::string string = {};

  if (value->getType()->isIntegerTy()) {
    string = "%d\n";
    value = CreateCast(value, builder->getInt32Ty());
  }

  if (value->getType()->isFloatTy()) {
    string = "%f\n";
    value = CreateCast(value, builder->getFloatTy());
  }

  llvm::Constant* fmt = llvm::ConstantDataArray::getString(*context, string);

  llvm::AllocaInst* alloca = builder->CreateAlloca(fmt->getType());
  builder->CreateStore(fmt, alloca);

  llvm::Value* formatted_string = builder->CreateBitCast(alloca, builder->getInt8PtrTy());

  llvm::Function* printf_function = module->getFunction("printf");

  if (printf_function == nullptr) {
    LOG_CRITICAL("No printf function in ir")
  }

  stack.Put(builder->CreateCall(printf_function, {formatted_string, value}, "printCall"));
}

void LLVMIRVisitor::Visit(ReturnStatement* statement) {
  LOG_DEBUG("In Return Statement")

  if (current_method->GetReturnType()->IsVoid()) {
    stack.Put(builder->CreateRetVoid());
  } else {
    llvm::Value* return_value = CreateCast(Accept(statement->expression), current_method->GetReturnType());
    stack.Put(builder->CreateRet(return_value));
  }
}

void LLVMIRVisitor::Visit(WhileStatement* statement) {
  LOG_DEBUG("In While Statement")
  stack.Pop();

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* while_cond = llvm::BasicBlock::Create(*context, "prewhile");
  llvm::BasicBlock* while_body = llvm::BasicBlock::Create(*context, "while");
  llvm::BasicBlock* while_merge = llvm::BasicBlock::Create(*context, "merge");
  function->getBasicBlockList().push_back(while_cond);
  function->getBasicBlockList().push_back(while_body);
  function->getBasicBlockList().push_back(while_merge);

  builder->CreateBr(while_cond);

  builder->SetInsertPoint(while_cond);

  llvm::Value* cond_value = CreateCast(Accept(statement->cond_expression), builder->getInt8Ty());
  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_value, builder->getInt1Ty(), true);

  builder->CreateCondBr(bool_cond_value, while_body, while_merge);

  builder->SetInsertPoint(while_body);

  ScopeGoDown();
  Visit(statement->statement);
  ScopeGoUp();
  stack.Pop();

  /*
    TODO change for non cond jump
  */

  builder->CreateBr(while_cond);

  builder->SetInsertPoint(while_merge);

  stack.Put(while_merge);
}

void LLVMIRVisitor::Visit(StatementList* statement) {
  LOG_DEBUG("In Statement List")
  statement->Accept(this);
}

void LLVMIRVisitor::Visit(LocalVariableStatement* statement) {
  stack.Pop();

  statement->variable_declaration->Accept(this);
}

void LLVMIRVisitor::Visit(StatementListStatement* statement) {
  LOG_DEBUG("In Statement List")
  ScopeGoDown();
  Visit(statement->statement_list);
  ScopeGoUp();
}

llvm::Value* LLVMIRVisitor::Accept(AstNode* ast_node) {
  ast_node->Accept(this);
  return stack.TopAndPop();
}

void LLVMIRVisitor::InitializeLLVM(const std::string& module_name) {
  LOG_TRACE("Initializing LLVM context")

  context = new llvm::LLVMContext();
  module = new llvm::Module(module_name, *context);
  builder = new llvm::IRBuilder<>(*context);

  pass_manager = new llvm::legacy::FunctionPassManager(module);

  pass_manager->add(llvm::createPromoteMemoryToRegisterPass());
  pass_manager->add(llvm::createInstructionCombiningPass());
  pass_manager->add(llvm::createReassociatePass());
  pass_manager->add(llvm::createGVNPass());
  pass_manager->add(llvm::createCFGSimplificationPass());
  pass_manager->doInitialization();
}

void LLVMIRVisitor::TerminateLLVM() {
  LOG_TRACE("Terminating LLVM context")

  delete pass_manager;

  delete builder;
  delete module;
  delete context;
}

void LLVMIRVisitor::Visit(LogicOpExpression* expression) {
  LOG_DEBUG("In LogicOp")

  llvm::Value* lhs = CreateCast(Accept(expression->lhs), builder->getInt8Ty());
  llvm::Value* rhs = CreateCast(Accept(expression->rhs), builder->getInt8Ty());

  llvm::Value* result = nullptr;

  switch (expression->operation) {
    case LogicOperation::OR:
      result = builder->CreateOr(lhs, rhs, "tmp_or");
      break;

    case LogicOperation::AND:
      result = builder->CreateAnd(lhs, rhs, "tmp_or");
      break;

    default:
    LOG_CRITICAL("uknown logic op: {}", (int) expression->operation);
  }

  stack.Put(CreateCast(result, builder->getInt8Ty()));
}

void LLVMIRVisitor::Visit(CompareOpExpression* expression) {
  LOG_DEBUG("In CompOp")

  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  LOG_DEBUG("before common: lhs_id({}) {} rhs_id({})",
            lhs->getType()->getTypeID(),
            GetCompareStrOp(expression->operation),
            rhs->getType()->getTypeID())

  CastToCommonType(&lhs, &rhs);

  LOG_DEBUG("after common: lhs_id({}) {} rhs_id({})",
            lhs->getType()->getTypeID(),
            GetCompareStrOp(expression->operation),
            rhs->getType()->getTypeID())

  llvm::Value* result = nullptr;

  switch (expression->operation) {
    case CompareOperation::EQUAL:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateICmpEQ(lhs, rhs, "eq");
      } else {
        result = builder->CreateFCmpOEQ(lhs, rhs, "eq");
      }
      break;

    case CompareOperation::NEQUAL:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateICmpNE(lhs, rhs, "ne");
      } else {
        result = builder->CreateFCmpONE(lhs, rhs, "ne");
      }
      break;

    case CompareOperation::LESS:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateICmpSLT(lhs, rhs, "lt");
      } else {
        result = builder->CreateFCmpOLT(lhs, rhs, "lr");
      }
      break;

    case CompareOperation::GREATER:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateICmpSGT(lhs, rhs, "gt");
      } else {
        result = builder->CreateFCmpOGT(lhs, rhs, "gt");
      }
      break;

    default:
    LOG_CRITICAL("uknown compare op: {}", (int) expression->operation);
  }

  stack.Put(result);
}

void LLVMIRVisitor::Visit(MathOpExpression* expression) {
  LOG_DEBUG("In MathOp")

  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  LOG_DEBUG("before common: lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetMathStrOp(expression->operation),
            rhs->getType()->getTypeID())

  CastToCommonType(&lhs, &rhs);

  LOG_DEBUG("after common: lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetMathStrOp(expression->operation),
            rhs->getType()->getTypeID())

  llvm::Value* result = nullptr;

  switch (expression->operation) {
    case MathOperation::PLUS:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateAdd(lhs, rhs, "add");
      } else {
        result = builder->CreateFAdd(lhs, rhs, "add");
      }
      break;

    case MathOperation::MINUS:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateSub(lhs, rhs, "sub");
      } else {
        result = builder->CreateFSub(lhs, rhs, "sub");
      }
      break;

    case MathOperation::MUL:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateMul(lhs, rhs, "mul");
      } else {
        result = builder->CreateFMul(lhs, rhs, "mul");
      }
      break;

    case MathOperation::DIV:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateSDiv(lhs, rhs, "div");
      } else {
        result = builder->CreateFDiv(lhs, rhs, "div");
      }
      break;

    case MathOperation::PERCENT:
      if (lhs->getType()->isIntegerTy()) {
        result = builder->CreateSRem(lhs, rhs, "srem");
      } else {
        result = builder->CreateFRem(lhs, rhs, "frem");
      }
      break;

    default:
    LOG_CRITICAL("uknown math op: {}", (int) expression->operation);
  }

  stack.Put(result);
}

void LLVMIRVisitor::Visit(ArrayIdxExpression* expression) {
  llvm::Value* arr_struct_ptr = Accept(expression->expr); //ptr to array struct
  llvm::Value* idx = Accept(expression->idx); //int

  llvm::PointerType* arr_struct_type = (llvm::PointerType*) arr_struct_ptr->getType();

  llvm::Value* arr_ptr = builder->CreateGEP(
    arr_struct_type->getElementType(),
    arr_struct_ptr,
    //builder->CreateLoad(arr_struct_ptr->getType(), arr_struct_ptr),
    llvm::ArrayRef<llvm::Value*>({
      llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), 0),
      llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), 0)
    })
  );

  //stack.Put(arr_ptr);
  //builder->CreateLoad(arr_ptr->getType()->getPointerElementType(),

  stack.Put(builder->CreateLoad(arr_ptr->getType()->getPointerElementType()->getPointerElementType(), builder->CreateGEP(
    arr_ptr->getType()->getPointerElementType()->getPointerElementType(),
    //arr_ptr,
    builder->CreateLoad(arr_ptr->getType()->getPointerElementType(), arr_ptr),
    llvm::ArrayRef<llvm::Value*>({idx})
    )
  ));

}

void LLVMIRVisitor::Visit(LengthExpression* expression) {
  llvm::Value* arr_struct_ptr = Accept(expression->identifier); //ptr to array struct

  llvm::PointerType* arr_struct_type = (llvm::PointerType*) arr_struct_ptr->getType();

  llvm::Value* len = builder->CreateGEP(
    arr_struct_type->getElementType(),
    arr_struct_ptr,
    //builder->CreateLoad(arr_struct_ptr->getType(), arr_struct_ptr),
    llvm::ArrayRef<llvm::Value*>({
                                   llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), 0),
                                   llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), 1)
                                 })
  );

  stack.Put(builder->CreateLoad(len->getType()->getPointerElementType(), len));
}

void LLVMIRVisitor::Visit(MethodCallExpression* expression) {
  expression->call->Accept(this);
}

void LLVMIRVisitor::Visit(NewArrayExpression* expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(NewClassExpression* expression) {
  llvm::Type* class_type = GetLLVMType(expression->type);

  llvm::Value* tmp_class_ptr = builder->CreateConstGEP1_64(
    llvm::Constant::getNullValue(class_type->getPointerTo()), 1, "class size"
  );
  llvm::Value* class_size = builder->CreatePointerCast(tmp_class_ptr, llvm::Type::getInt64Ty(*context));

  //llvm::TypeSize type_size = module->getDataLayout().getTypeAllocSize(class_type);
  //type_size.getFixedSize();

  llvm::Value* void_ptr = builder->CreateCall(module->getFunction("GC_malloc"), class_size);
  llvm::Value* class_ptr = builder->CreateBitCast(void_ptr, class_type);

  stack.Put(class_ptr);
}

void LLVMIRVisitor::Visit(ThisExpression* expression) {
  last_expr_class = current_class;
  stack.Put(current_this);
}

void LLVMIRVisitor::Visit(CommaExpressionList* list) {
  assert(!"not used");
}

void LLVMIRVisitor::Visit(MethodCall* call) {
  llvm::Value* this_arg = Accept(call->caller);
  llvm::Function* method = module->getFunction(GenMethodName(last_expr_class, call->function_name.name));

  std::vector<llvm::Value*> args{this_arg};
  for (int arg_no = 1; arg_no < method->arg_size(); ++arg_no) {
    llvm::Value* arg_val = Accept(call->expression_list->elements.at(arg_no - 1));
    args.push_back(CreateCast(arg_val, method->getArg(arg_no)->getType()));
  }

  if (method->getReturnType()->isVoidTy()) {
    stack.Put(builder->CreateCall(method, args));
  } else {
    stack.Put(builder->CreateCall(method, args, GenMethodName(last_expr_class, call->function_name.name) + " call"));
  }
}

void LLVMIRVisitor::Visit(AssertStatement* statement) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(MethodCallStatement* statement) {
  statement->call->Accept(this);
  stack.Pop();
}

void LLVMIRVisitor::Visit(ArrayLValue* statement) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(FieldLValue* statement) {
  assert(!"not used");
}

void LLVMIRVisitor::Visit(IdentifierLValue* statement) {
  std::shared_ptr<IRObject> obj = current_scope->GetFromAnywhere(statement->name);
  if (obj->IsLocal()) {
    stack.Put(obj->Get());
  } else if (obj->IsField()) {
    stack.Put(builder->CreateGEP(
    module->getTypeByName(current_class->GetName().name),
      builder->CreateLoad(GetLLVMType(current_class), current_this),
      llvm::ArrayRef<llvm::Value*>({
        llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), 0),
        llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)),
                                      symbol_tree->GetClassTable()->GetInfo(current_class).GetFieldNo(statement->name))}
        )
      )
    );
    /*
     *
    stack.Put(builder->CreateStructGEP(
      builder->CreateLoad(module->getTypeByName(current_class->GetName().name), builder->CreateLoad(current_this->getType(), current_this)), /*all field are private so ptr to only current this
    table->GetClassTable()->GetInfo(current_class).GetFieldNo(statement->name)
      )
    );
    */
  }
  //create load from
}

void LLVMIRVisitor::Visit(FieldDeclaration* declaration) {
  //pass, see GenerateClassesDecl()
}

void LLVMIRVisitor::GenerateStandartLib() {
  llvm::FunctionType* printf_type = llvm::FunctionType::get(
    builder->getInt32Ty(),
    {builder->getInt8PtrTy()},
    true
  );

  llvm::Function::Create(
    printf_type, llvm::Function::ExternalLinkage,
    "printf",
    *module
  );

  //TODO use GC_malloc
  llvm::FunctionType* malloc_type = llvm::FunctionType::get(
    builder->getInt8PtrTy(),
    {builder->getInt64Ty()},
    false
  );

  llvm::Function::Create(
    malloc_type, llvm::Function::ExternalLinkage,
    "GC_malloc",
    *module
  );
}

void LLVMIRVisitor::ScopeGoUp() {
  current_scope.GoUp();
}

void LLVMIRVisitor::ScopeGoDown() {
  current_scope.GoDown();
}

void LLVMIRVisitor::GenerateClassesDecl() {
  for (const auto& entry: symbol_tree->GetClassTable()->GetAllInfo()) {
    LOG_DEBUG("Created {}", entry.first->ToString())
    llvm::StructType::create(*context, llvm::StringRef(entry.first->GetName().name));
  }

  for (const auto& entry: symbol_tree->GetClassTable()->GetAllInfo()) {
    llvm::StructType* class_type = module->getTypeByName(entry.first->GetName().name);
    std::vector<llvm::Type*> fields_types;
    for (const auto& field: entry.second.GetAllFields()) {
      fields_types.push_back(GetLLVMType(field.type));
    }
    class_type->setBody(llvm::ArrayRef<llvm::Type*>(fields_types));
  }
}

void LLVMIRVisitor::GenerateMethodsDecl() {
  for (const auto& class_entry: symbol_tree->GetClassTable()->GetAllInfo()) {
    for (const auto& method_entry: class_entry.second.GetAllMethods()) {
      //first arg is class
      std::vector<llvm::Type*> param_types({GetLLVMType(class_entry.first)});

      for (const auto& param_entry: method_entry.second->GetArgs()) {
        param_types.push_back(GetLLVMType(param_entry.type));
      }

      llvm::FunctionType* method_type = llvm::FunctionType::get(
        GetLLVMType(method_entry.second->GetReturnType()),
        param_types,
        false
      );

      llvm::Function::Create(
        method_type, llvm::Function::InternalLinkage,
        GenMethodName(class_entry.first, method_entry.second),
        *module);
    }
  }
}

std::string LLVMIRVisitor::GenMethodName(SharedPtr<ClassType> class_type, SharedPtr<MethodType> method_type) {
  return class_type->GetName().name + "@" + method_type->GetName().name;
}

std::string LLVMIRVisitor::GenMethodName(SharedPtr<ClassType> class_type,
                                         const std::string& method_name) {
  return class_type->GetName().name + "@" + method_name;
}

std::string LLVMIRVisitor::GenArrayName(const SharedPtr<ArrayType>& array_type) {
  return "Array" + array_type->GetElemType()->ToString();
}

llvm::Type* LLVMIRVisitor::GetLLVMType(const SharedPtr<Type>& type) {
  if (type->IsClass()) {
    return module->getTypeByName(
      llvm::StringRef(
        std::reinterpret_pointer_cast<ClassType>(type)->GetName().name
      ))->getPointerTo();
  } else if (type->IsArray()) {
    SharedPtr<ArrayType> array_type = std::reinterpret_pointer_cast<ArrayType>(type);
    
    llvm::StructType* llvm_array_type = module->getTypeByName(llvm::StringRef(GenArrayName(array_type)));

    if (llvm_array_type == nullptr) {
      llvm::StructType::create(*context, llvm::StringRef(GenArrayName(array_type)));
      llvm_array_type = module->getTypeByName(llvm::StringRef(GenArrayName(array_type)));

      std::vector<llvm::Type*> fields_types;

      fields_types.push_back(GetLLVMType(array_type->GetElemType())->getPointerTo()); //0th field (data)
      fields_types.push_back(builder->getInt32Ty());  //1th field (size)
      llvm_array_type->setBody(llvm::ArrayRef<llvm::Type*>(fields_types));
    }

    return llvm_array_type->getPointerTo();
  } else {
    switch (type->GetTypeId()) {
      case Type::TypeID::VoidTy:
        return llvm::Type::getVoidTy(*context);

      case Type::TypeID::IntTy:
        return llvm::Type::getInt32Ty(*context);

      case Type::TypeID::BoolTy:
        return llvm::Type::getInt8Ty(*context);

      default:
      LOG_CRITICAL("Unreachable code with type {}", type->ToString());
    }
  }
}

void LLVMIRVisitor::CreateStore(std::shared_ptr<IRObject> obj, llvm::Value* value) {
  assert(!"not used");
  //obj->Set(builder->CreateStore(value, obj->Get()));
}

llvm::Value* LLVMIRVisitor::CreateLoad(std::shared_ptr<IRObject> obj) {
  return builder->CreateLoad(GetLLVMType(obj->GetType()), obj->Get());
}

llvm::Value* LLVMIRVisitor::CreateCast(llvm::Value* value, llvm::Type* type) {
  if (value->getType()->isIntegerTy() && type->isIntegerTy()) {
    if (value->getType()->getIntegerBitWidth() != type->getIntegerBitWidth()) {
      return builder->CreateSExtOrTrunc(value, type);
      //return builder->CreateIntCast(value, type, true);
    } else {
      return value;
    }
  } else if (value->getType()->isFloatTy() && type->isIntegerTy()) {
    //TODO make float to int
    return value;
  } else if (value->getType()->isIntegerTy() && type->isFloatTy()) {
    //TODO make int to float
    return value;
  }

  LOG_DEBUG("returning uncasted default value")
  return value;
}

llvm::Value* LLVMIRVisitor::CreateCast(llvm::Value* value, const SharedPtr<Type>& type) {
  return CreateCast(value, GetLLVMType(type));
}

llvm::Type* LLVMIRVisitor::GetCommonType(llvm::Type* lhs, llvm::Type* rhs) {
  if (lhs->isFloatTy() || rhs->isFloatTy()) {
    return lhs;
  }

  // no floating here
  return llvm::Type::getIntNTy(*context, std::max(lhs->getIntegerBitWidth(), rhs->getIntegerBitWidth()));
}

void LLVMIRVisitor::CastToCommonType(llvm::Value** lhs, llvm::Value** rhs) {
  llvm::Type* common_type = GetCommonType((*lhs)->getType(), (*rhs)->getType());

  *lhs = CreateCast(*lhs, common_type);
  *rhs = CreateCast(*rhs, common_type);
}
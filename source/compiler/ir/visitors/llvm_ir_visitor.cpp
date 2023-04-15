#include "compiler/core/logger.hpp"

#include "llvm_ir_visitor.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

void LLVMIRVisitor::TranslateToIR(Program* program, std::unique_ptr<SymbolLayerTree> layer_tree, const std::filesystem::path& path) {
  LOG_TRACE("path: {}", path.native());

  this->table = std::move(layer_tree);
  current_scope = table->begin();
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

  llvm::Function* main = llvm::Function::Create(
    function_type,
    llvm::Function::InternalLinkage,
    "main",
    module
  );

  llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", main);

  builder->SetInsertPoint(entry);
  Visit(main_class->statement_list);
  builder->CreateRetVoid();

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

void LLVMIRVisitor::Visit(MethodDeclaration* method_declaration) {
  ScopeGoDown();
  LOG_DEBUG("In Method Declaration")

  assert(!"not ready");

  //emit method
  current_method = method_declaration->method_type;

  llvm::Function* method = module->getFunction(GenMethodName(current_class, method_declaration->method_type));
  llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", method);
  builder->SetInsertPoint(entry);

  //TODO alloca all variables of this scope;

  // initialise var env with function params
  for (const auto & arg : current_method->GetArgs()) {
    //llvm::Type *paramType = method->getFunctionType()->getParamType(paramNo);
    //
    //builder->CreateStore();
    //current_scope->GetFromAnywhere(arg.symbol)->Set();
  }


  stack.Pop();

  llvm::verifyFunction(*method);
  ScopeGoUp();
}

void LLVMIRVisitor::Visit(VariableDeclaration* declaration) {
  LOG_DEBUG("In Variable Declaration: [{}] {}", declaration->type->ToString(), declaration->identifier.name)

  //insert in the beginning for optimizer
  llvm::Function* function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock& block = function->getEntryBlock();

  llvm::IRBuilder<> tmp(&block, block.begin());

  //current_scope->GetFromCurrent(declaration->identifier);
  //CreateStore(current_scope->GetFromCurrent(declaration->identifier), )

  //llvm::Value* variable = tmp.CreateAlloca(builder->getInt32Ty(), nullptr, declaration->identifier.name);

  std::shared_ptr<IRObject> obj = current_scope->GetFromCurrent(declaration->identifier);
  obj->Set(tmp.CreateAlloca(builder->getInt32Ty(), nullptr, declaration->identifier.name));

  stack.Put(obj->Get());
  //table.Insert(declaration->identifier.name, variable);
}

void LLVMIRVisitor::Visit(TrueExpression* expression) {
  LOG_DEBUG("In True Expression")

  llvm::Value* val = llvm::ConstantInt::getSigned((llvm::Type::getInt8Ty(*context)), 1);
  stack.Put(val);

  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt8Ty());
  //llvm::Value* value = builder->getInt8(1);
  //builder->CreateAlignedStore(value, alloca, 1);
  //stack.Put(alloca);
}

void LLVMIRVisitor::Visit(FalseExpression* expression) {
  LOG_DEBUG("In False Expression")

  llvm::Value* val = llvm::ConstantInt::getSigned((llvm::Type::getInt8Ty(*context)), 0);
  stack.Put(val);

  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt8Ty());
  //llvm::Value* value = builder->getInt8(0);
  //builder->CreateAlignedStore(value, alloca, 1);
  //stack.Put(alloca);
}

void LLVMIRVisitor::Visit(IdentifierExpression* expression) {
  LOG_DEBUG("In Identifier Expression: {}", expression->identifier.name)

  stack.Put(CreateLoad(current_scope->GetFromAnywhere(expression->identifier)));
  //current_scope->GetFromAnywhere()->Get()
  //stack.GetData().push_back(class_table.Get(expression->identifier));
  //stack.Put(table.Get(expression->identifier.name));
}

void LLVMIRVisitor::Visit(IntegerExpression* expression) {
  LOG_DEBUG("In Integer Expression: {}", expression->value)

  llvm::Value* val = llvm::ConstantInt::getSigned((llvm::Type::getInt32Ty(*context)), expression->value);
  stack.Put(val);

  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt32Ty());
  //llvm::Value* value = builder->getInt32(expression->value);
  //builder->CreateStore(value, alloca);

  //stack.Put(alloca);
  //stack.GetData().push_back(alloca);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
  LOG_DEBUG("In Not Expression")

  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  //llvm::Value* true_val = builder->getInt1(true);
  //builder->CreateStore(value, alloca);
  //stack.Put(alloca);
  llvm::Value* val = Accept(expression->expression);
  stack.Put(builder->CreateNot(val, "not"));

  //llvm::Value* result = builder->CreateNot(val, "not");
  //stack.Put(builder->CreateXor(val, true_val));
}

void LLVMIRVisitor::Visit(AssignmentStatement* statement) {
  LOG_DEBUG("In Assignment Statement")
  stack.Pop();

  //var == ptr to var
  llvm::Value* var = Accept(statement->value);
  llvm::Value* expr = Accept(statement->expression);

  stack.Put(builder->CreateStore(CreateCast(expr, var->getType()), var));

  //llvm::LoadInst* load_expr = builder->CreateLoad(builder->getInt32Ty(), expr);
  //llvm::Value* var = class_table.Get(statement->identifier);

  //stack.Put(builder->CreateStore(load_expr, var));
}

void LLVMIRVisitor::Visit(IfElseStatement* statement) {
  LOG_DEBUG("In IfElse Statement")
  stack.Pop();

  llvm::Value* cond_expr = CreateCast(Accept(statement->cond_expression), builder->getInt8Ty());

  //llvm::Value* cmp = builder->CreateAlignedLoad(builder->getInt8Ty(), Accept(statement->cond_expression), true);
  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_expr, builder->getInt1Ty(), true);

  llvm::Value* cmp = builder->CreateICmpEQ(bool_cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* then_block  = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block  = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cmp, then_block, else_block);

  builder->SetInsertPoint(then_block);

  ScopeGoDown();
  Visit(statement->statement_true);
  ScopeGoUp();

  stack.Pop();
  //Accept(statement->statement_true);
  builder->CreateBr(merge_block);

  //then_block = builder->GetInsertBlock();

  function->getBasicBlockList().push_back(else_block);
  builder->SetInsertPoint(else_block);

  ScopeGoDown();
  Visit(statement->statement_false);
  ScopeGoUp();

  stack.Pop();

  builder->CreateBr(merge_block);

  //else_block = builder->GetInsertBlock();

  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);

  stack.Put(merge_block);
  //LOG_DEBUG("then_value: {}", then_value->getType()->getTypeID());
  //LOG_DEBUG("else_value: {}", else_value->getType()->getTypeID());

  //llvm::PHINode* phi_node = builder->CreatePHI(then_value->getType(), 2, "iftmp");

  //phi_node->addIncoming(then_value, then_block);
  //phi_node->addIncoming(else_value, else_block);
  //stack.Put(phi_node);
}

void LLVMIRVisitor::Visit(IfStatement* statement) {
  LOG_DEBUG("In If Statement")
  stack.Pop();

  llvm::Value* cond_expr = CreateCast(Accept(statement->cond_expression), builder->getInt8Ty());

  //llvm::Value* cond_value = builder->CreateAlignedLoad(builder->getInt8Ty(), Accept(statement->cond_expression), true);
  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_expr, builder->getInt1Ty(), true);
  llvm::Value* cmp = builder->CreateICmpEQ(bool_cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* then_block  = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block  = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cmp, then_block, else_block);

  builder->SetInsertPoint(then_block);

  ScopeGoDown();
  Visit(statement->statement_true);
  ScopeGoUp();

  stack.Pop();
  //llvm::Value* then_value = Accept(statement->statement_true);
  builder->CreateBr(merge_block);

  function->getBasicBlockList().push_back(else_block);
  builder->SetInsertPoint(else_block);
  builder->CreateBr(merge_block);

  //then_block = builder->GetInsertBlock();

  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);

  stack.Put(merge_block);
  //llvm::PHINode* phi_node = builder->CreatePHI(llvm::SharedPtr<Type>::getInt32Ty(*context), 1, "iftmp");
  //llvm::PHINode* phi_node = builder->CreatePHI(then_value->getType(), 1, "iftmp");

  //phi_node->addIncoming(then_value, then_block);
  //stack.Put(phi_node);
}

void LLVMIRVisitor::Visit(PrintStatement* statement) {
  LOG_DEBUG("In Print Statement")
  stack.Pop();

  llvm::Value* value = Accept(statement->expression);

  std::string string = {};

  if (value->getType()->isIntegerTy()) {
    string = "%d";
    value = CreateCast(value, builder->getInt32Ty());
  }

  if (value->getType()->isFloatTy()) {
    string = "%f";
    value = CreateCast(value, builder->getFloatTy());
  }

  //std::string string = "%d\n";
  llvm::Constant* fmt = llvm::ConstantDataArray::getString(*context, string);

  llvm::AllocaInst* alloca = builder->CreateAlloca(fmt->getType());
  builder->CreateStore(fmt, alloca);

  // cast string to char*
  llvm::Value* formatted_string = builder->CreateBitCast(alloca, builder->getInt8PtrTy());

  //llvm::Value* pointer = Accept(statement->expression);

  //llvm::LoadInst* value = builder->CreateLoad(builder->getInt32Ty(), pointer);

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

  //builder->CreateAlloca(builder->getInt1Ty(), llvm::ConstantInt::getTrue(*context), "nop");
  //builder->CreateAdd(llvm::ConstantInt::getTrue(*context), llvm::ConstantInt::getTrue(*context), "nop");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  llvm::BasicBlock* while_cond = llvm::BasicBlock::Create(*context, "prewhile");
  llvm::BasicBlock* while_body  = llvm::BasicBlock::Create(*context, "while");
  llvm::BasicBlock* while_merge  = llvm::BasicBlock::Create(*context, "merge");
  function->getBasicBlockList().push_back(while_cond);
  function->getBasicBlockList().push_back(while_body);
  function->getBasicBlockList().push_back(while_merge);

  builder->CreateBr(while_cond);

  builder->SetInsertPoint(while_cond);

  llvm::Value* cond_value = CreateCast(Accept(statement->cond_expression), builder->getInt8Ty());
  //llvm::Value* cond_value = builder->CreateAlignedLoad(builder->getInt8Ty(), Accept(statement->cond_expression), true);
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
  //llvm::Value* cond_br = builder->CreateCondBr(Accept(statement->cond_expression), while_body, while_merge);

  builder->SetInsertPoint(while_merge);

  stack.Put(while_merge);
}

void LLVMIRVisitor::Visit(StatementList* statement) {
  LOG_DEBUG("In Statement List")
  statement->Accept(this);
}

void LLVMIRVisitor::Visit(LocalVariableStatement* statement) {
  LOG_DEBUG("In Local Var Declaration: int {}", statement->variable_declaration->identifier.name)
  stack.Pop();

  statement->variable_declaration->Accept(this);
  //stack.Put(table.Get(statement->variable_declaration->identifier.name));
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
}

void LLVMIRVisitor::TerminateLLVM() {
  LOG_TRACE("Terminating LLVM context")

  delete builder;
  delete module;
  delete context;
}

void LLVMIRVisitor::Visit(LogicOpExpression* expression) {
  LOG_DEBUG("In LogicOp")

  llvm::Value* lhs = CreateCast(Accept(expression->lhs), builder->getInt8Ty());
  llvm::Value* rhs = CreateCast(Accept(expression->rhs), builder->getInt8Ty());

  /*
  LOG_DEBUG("before common: lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetLogicStrOp(expression->operation),
            rhs->getType()->getTypeID())

  CastToCommonType(lhs, rhs);

  LOG_DEBUG("after common: lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetLogicStrOp(expression->operation),
            rhs->getType()->getTypeID())
  */
  //llvm::LoadInst* lhs = builder->CreateLoad(builder->getInt8Ty(), lhs);
  //llvm::LoadInst* rhs = builder->CreateLoad(builder->getInt8Ty(), rhs);
  llvm::Value* result = nullptr;

  switch(expression->operation) {
    case LogicOperation::OR:
      result = builder->CreateOr(lhs, rhs, "tmp_or");
      break;

    case LogicOperation::AND:
      result = builder->CreateAnd(lhs, rhs, "tmp_or");
      break;

    default:
      LOG_CRITICAL("uknown logic op: {}", (int) expression->operation);
  }

  //llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt8Ty());
  //builder->CreateAlignedStore(result, alloca_result, 1);

  stack.Put(CreateCast(result, builder->getInt8Ty()));

  //stack.Put(alloca_result);
}

void LLVMIRVisitor::Visit(CompareOpExpression* expression) {
  LOG_DEBUG("In CompOp")

  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  LOG_DEBUG("before common: lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetCompareStrOp(expression->operation),
            rhs->getType()->getTypeID())

  CastToCommonType(&lhs, &rhs);

  LOG_DEBUG("after common: lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetCompareStrOp(expression->operation),
            rhs->getType()->getTypeID())

  llvm::Value* result = nullptr;

  //llvm::Value* lhs = builder->CreateIntCast(builder->CreateAlignedLoad(builder->getInt32Ty(), lhs, 4), builder->getInt32Ty(), true);
  //llvm::Value* rhs = builder->CreateIntCast(builder->CreateAlignedLoad(builder->getInt32Ty(), rhs, 4), builder->getInt32Ty(), true);

  switch(expression->operation) {
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

  /*
  llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt8Ty());
  builder->CreateStore(builder->CreateIntCast(result, builder->getInt8Ty(), true), alloca_result);

  stack.Put(alloca_result);
  */
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
  //llvm::Value* lhs = builder->CreateAlignedLoad(builder->getInt32Ty(), lhs, 4);
  //llvm::Value* rhs = builder->CreateAlignedLoad(builder->getInt32Ty(), rhs, 4);

  switch(expression->operation) {
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

  //llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt32Ty());
  //builder->CreateStore(result, alloca_result);

  //stack.Put(alloca_result);
}

void LLVMIRVisitor::Visit(ArrayIdxExpression *expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(LengthExpression *expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(MethodCallExpression *expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(NewArrayExpression *expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(NewClassExpression *expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(ThisExpression *expression) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(CommaExpressionList *program) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(MethodCall *program) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(AssertStatement *statement) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(MethodCallStatement *statement) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(ArrayLValue *statement) {
  assert(!"not supported");
}

void LLVMIRVisitor::Visit(FieldLValue *statement) {
  assert(!"pass");
}

void LLVMIRVisitor::Visit(IdentifierLValue *statement) {
  stack.Put(current_scope->GetFromAnywhere(statement->name)->Get());
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
  /*
  module->getOrInsertFunction(
    "println",
    llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(*context),
                            llvm::Type::getInt8PtrTy(*context),
    true));
  */
  /*
  module->getOrInsertFunction(
    "malloc",
    llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context),
                            llvm::IntegerType::getInt64Ty(*context),
                            false));
  */
  //TODO use GC_malloc
  llvm::FunctionType* malloc_type = llvm::FunctionType::get(
    builder->getInt64Ty(),
    {llvm::Type::getInt8PtrTy(*context)},
    false
  );

  llvm::Function::Create(
    malloc_type, llvm::Function::ExternalLinkage,
    "malloc",
    *module
  );
}

void LLVMIRVisitor::ScopeGoUp() {
  current_scope.GoUp();
}

void LLVMIRVisitor::ScopeGoDown() {
  current_scope.GoDown();
}

void LLVMIRVisitor::ScopeGoDownWithAlloc() {
  current_scope.GoDown();
  /*
  for (const auto& object : current_scope->GetAllFromCurrent()) {
    
  }
  */
}

void LLVMIRVisitor::GenerateClassesDecl() {
  for (const auto& entry : table->GetClassTable()->GetAllInfo()) {
    llvm::StructType::create(*context, llvm::StringRef(entry.first->GetName().name));
  }

  for (const auto& entry : table->GetClassTable()->GetAllInfo()) {
    llvm::StructType* class_type = module->getTypeByName(llvm::StringRef(entry.first->GetName().name));
    std::vector<llvm::Type*> fields_types;
    for (const auto& field : entry.second.GetAllFields()) {
      fields_types.push_back(GetLLVMType(field.type));
    }
    class_type->setBody(llvm::ArrayRef<llvm::Type*>(fields_types));
  }
}

void LLVMIRVisitor::GenerateMethodsDecl() {
  for (const auto & class_entry : table->GetClassTable()->GetAllInfo()) {
    for (const auto& method_entry : class_entry.second.GetAllMethods()) {
      //first arg is class
      std::vector<llvm::Type*> param_types({GetLLVMType(class_entry.first)});

      for (const auto& param_entry : method_entry.second->GetArgs()) {
        param_types.push_back(GetLLVMType(param_entry.type));
      }

      llvm::FunctionType* method_type = llvm::FunctionType::get(
        GetLLVMType(method_entry.second->GetReturnType()),
        param_types,
        false
      );

      llvm::Function::Create(method_type, llvm::Function::InternalLinkage,
                             GenMethodName(class_entry.first, method_entry.second),
                             *module);

    }
  }
}

std::string LLVMIRVisitor::GenMethodName(SharedPtr<ClassType> class_type, SharedPtr<MethodType> method_type) {
  return class_type->GetName().name + "@" + method_type->GetName().name;
}

llvm::Type* LLVMIRVisitor::GetLLVMType(const SharedPtr<Type>& type) {
  if (type->IsClass()) {
    return module->getTypeByName(llvm::StringRef(
      std::reinterpret_pointer_cast<ClassType>(type)->GetName().name))->getPointerTo();
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
    assert(!"not  used");
    //obj->Set(builder->CreateStore(value, obj->Get()));
}

llvm::Value* LLVMIRVisitor::CreateLoad(std::shared_ptr<IRObject> obj) {
  return builder->CreateLoad(GetLLVMType(obj->GetType()), obj->Get());
}

llvm::Value* LLVMIRVisitor::CreateCast(llvm::Value* value, llvm::Type* type) {
  if (value->getType()->isIntegerTy() && type->isIntegerTy()) {
      if (value->getType()->getIntegerBitWidth() != type->getIntegerBitWidth()) {
          return builder->CreateIntCast(value, type, true);
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

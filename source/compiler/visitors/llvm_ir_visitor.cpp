#include "compiler/core/logger.hpp"

#include "llvm_ir_visitor.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

void LLVMIRVisitor::TranslateToIR(Program* program, const std::filesystem::path& path) {
  LOG_TRACE("path: {}", path.native());

  table.Clear();
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
  program->main_class->Accept(this);
}

void LLVMIRVisitor::Visit(MainClass* main_class) {
  LOG_DEBUG("In MainClass Declaration")

  llvm::FunctionType* function_type = llvm::FunctionType::get(
    llvm::Type::getVoidTy(*context), false
  );

  llvm::Function* main = llvm::Function::Create(
    function_type,
    llvm::Function::ExternalLinkage,
    "main",
    module
  );

  llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", main);

  builder->SetInsertPoint(entry);
  
  main_class->statement_list->Accept(this);
  
  builder->CreateRetVoid();
}

void LLVMIRVisitor::Visit(ClassDeclaration* class_declaration) {
  //some class stuff
  return;
}

void LLVMIRVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  LOG_DEBUG("In Class-Decalration List")
  class_declaration_list->Accept(this);
}

void LLVMIRVisitor::Visit(DeclarationList* declaration_list) {
  LOG_DEBUG("In Declaration List")
  declaration_list->Accept(this);
}

void LLVMIRVisitor::Visit(MethodDeclaration* method_declaration) {
  LOG_DEBUG("In Method Declaration")
  //some class stuff
  return;
}

void LLVMIRVisitor::Visit(VariableDeclaration* variable_declaration) {
  LOG_DEBUG("In Variable Declaration: int {}", variable_declaration->identifier.name)

  llvm::Function* function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock& block = function->getEntryBlock();

  llvm::IRBuilder<> tmp(&block, block.begin());
  llvm::Value* variable = tmp.CreateAlloca(builder->getInt32Ty(), nullptr, variable_declaration->identifier.name);
  table.Insert(variable_declaration->identifier.name, variable);
}

void LLVMIRVisitor::Visit(TrueExpression* expression) {
  LOG_DEBUG("In True Expression")

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt8Ty());
  llvm::Value* value = builder->getInt8(1);
  builder->CreateAlignedStore(value, alloca, 1);
  stack.Put(alloca);
}

/*
void LLVMIRVisitor::Visit(BinOpExpression* expression) {
  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  llvm::Value* result = nullptr;
  llvm::LoadInst* load_lhs = nullptr;
  llvm::LoadInst* load_rhs = nullptr;

  LOG_DEBUG("IN BinOp lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetBinOp(expression->operation),
            rhs->getType()->getTypeID())

  switch(expression->operation) {
    case BinOperation::PLUS:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      result = builder->CreateAdd(load_lhs, load_rhs, "addtmp");
      break;

    case BinOperation::MINUS:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      result = builder->CreateSub(load_lhs, load_rhs, "subtmp");
      break;

    case BinOperation::MUL:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      result = builder->CreateMul(load_lhs, load_rhs, "multmp");
      break;

    case BinOperation::DIV:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      result = builder->CreateFDiv(load_lhs, load_rhs, "divtmp");
      break;

    case BinOperation::EQUAL:
      result = builder->CreateICmpEQ(lhs, rhs, "tmp_eq");
      break;

    case BinOperation::NEQUAL:
      result = builder->CreateICmpNE(lhs, rhs, "tmp_ne");
      break;

    case BinOperation::LESS:
      result = builder->CreateICmpSLT(lhs, rhs, "tmp_lt");
      break;

    case BinOperation::GREATER:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      result = builder->CreateICmpSGT(load_lhs, load_rhs, "cmp_gt");
      break;

    case BinOperation::OR:
      result = builder->CreateOr(lhs, rhs, "tmp_or");
      break;

    case BinOperation::AND:
      result = builder->CreateAnd(lhs, rhs, "tmp_or");
      break;

    case BinOperation::PERCENT:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      result = builder->CreateSRem(load_lhs, load_rhs, "tmp_rem");
      break;

    default:
    LOG_CRITICAL("uknown binary op: {}", (int) expression->operation);
      break;
  }

  llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt32Ty());
  builder->CreateStore(result, alloca_result);

  stack.Put(alloca_result);
}
 */

void LLVMIRVisitor::Visit(FalseExpression* expression) {
  LOG_DEBUG("In False Expression")

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt8Ty());
  llvm::Value* value = builder->getInt8(0);
  builder->CreateAlignedStore(value, alloca, 1);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(IdentifierExpression* expression) {
  LOG_DEBUG("In Identifier Expression: {}", expression->identifier)
  //stack.GetData().push_back(table.Get(expression->identifier));
  stack.Put(table.Get(expression->identifier));
}

void LLVMIRVisitor::Visit(IntegerExpression* expression) {
  LOG_DEBUG("In Integer Expression: {}", expression->value)

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt32Ty());
  llvm::Value* value = builder->getInt32(expression->value);
  builder->CreateStore(value, alloca);

  stack.Put(alloca);
  //stack.GetData().push_back(alloca);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
  LOG_DEBUG("In Not Expression")

  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  //llvm::Value* true_val = builder->getInt1(true);
  //builder->CreateStore(value, alloca);
  //stack.Put(alloca);
  llvm::Value* val = Accept(expression->expression);

  llvm::Value* result = builder->CreateNot(val, "not");
  stack.Put(result);
  //stack.Put(builder->CreateXor(val, true_val));
}

void LLVMIRVisitor::Visit(AssignmentStatement* statement) {
  LOG_DEBUG("In Assignment Statement")
  stack.Pop();

  llvm::Value* expr = Accept(statement->expression);
  llvm::LoadInst* load_expr = builder->CreateLoad(builder->getInt32Ty(), expr);
  //llvm::Value* var = table.Get(statement->identifier);

  //stack.Put(builder->CreateStore(load_expr, var));
}

void LLVMIRVisitor::Visit(IfElseStatement* statement) {
  LOG_DEBUG("In IfElse Statement")
  stack.Pop();

  llvm::Value* cond_value = builder->CreateAlignedLoad(builder->getInt8Ty(), Accept(statement->cond_expression), true);
  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_value, builder->getInt1Ty(), true);

  cond_value = builder->CreateICmpEQ(bool_cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* then_block  = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block  = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cond_value, then_block, else_block);

  builder->SetInsertPoint(then_block);
  Accept(statement->statement_true);
  builder->CreateBr(merge_block);

  then_block = builder->GetInsertBlock();

  function->getBasicBlockList().push_back(else_block);
  builder->SetInsertPoint(else_block);

  Accept(statement->statement_false);

  builder->CreateBr(merge_block);

  else_block = builder->GetInsertBlock();

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

  llvm::Value* cond_value = builder->CreateAlignedLoad(builder->getInt8Ty(), Accept(statement->cond_expression), true);
  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_value, builder->getInt1Ty(), true);

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* then_block  = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block  = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(bool_cond_value, then_block, else_block);

  builder->SetInsertPoint(then_block);
  llvm::Value* then_value = Accept(statement->statement_true);
  builder->CreateBr(merge_block);

  function->getBasicBlockList().push_back(else_block);
  builder->SetInsertPoint(else_block);
  builder->CreateBr(merge_block);

  then_block = builder->GetInsertBlock();

  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);

  stack.Put(merge_block);
  //llvm::PHINode* phi_node = builder->CreatePHI(llvm::Type::getInt32Ty(*context), 1, "iftmp");
  //llvm::PHINode* phi_node = builder->CreatePHI(then_value->getType(), 1, "iftmp");

  //phi_node->addIncoming(then_value, then_block);
  //stack.Put(phi_node);
}

void LLVMIRVisitor::Visit(PrintStatement* statement) {
  LOG_DEBUG("In Print Statement")
  stack.Pop();

  std::string string = "%d\n";
  llvm::Constant* fmt = llvm::ConstantDataArray::getString(*context, string);

  llvm::AllocaInst* alloca = builder->CreateAlloca(fmt->getType());
  builder->CreateStore(fmt, alloca);

  // cast string to char*
  llvm::Value* formatted_string = builder->CreateBitCast(alloca, builder->getInt8PtrTy());

  llvm::Value* pointer = Accept(statement->expression);

  llvm::LoadInst* value = builder->CreateLoad(builder->getInt32Ty(), pointer);

  llvm::PointerType* pointer_type = builder->getInt8PtrTy();

  llvm::Function* printf_function = module->getFunction("printf");

  if (printf_function == nullptr) {
    llvm::FunctionType* printf_type = llvm::FunctionType::get(
      builder->getInt32Ty(),
      {pointer_type},
      true
    );

    printf_function = llvm::Function::Create(
      printf_type, llvm::Function::ExternalLinkage,
      "printf",
      *module
    );
  }

  stack.Put(builder->CreateCall(printf_function, {formatted_string, value}, "printCall"));
}

void LLVMIRVisitor::Visit(ReturnStatement* statement) {
  LOG_DEBUG("In Return Statement")
  stack.Pop();
  // do fun stuff
  return;
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

  llvm::Value* cond_value = builder->CreateAlignedLoad(builder->getInt8Ty(), Accept(statement->cond_expression), true);
  llvm::Value* bool_cond_value = builder->CreateIntCast(cond_value, builder->getInt1Ty(), true);

  builder->CreateCondBr(bool_cond_value, while_body, while_merge);

  builder->SetInsertPoint(while_body);

  statement->statement->Accept(this);
  stack.Pop();

  /*
    change for non cond jump
  */
  // we now need to conditionally loop back to the body of the while loop if
  // the condition (which we are re-evaluating) is still true, otherwise we
  // branch to the merge point
  builder->CreateBr(while_cond);
  //llvm::Value* cond_br = builder->CreateCondBr(Accept(statement->cond_expression), while_body, while_merge);

  // and lastly, we want all new statements after the while to go into the
  // merge case
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
  stack.Put(table.Get(statement->variable_declaration->identifier.name));
}

void LLVMIRVisitor::Visit(StatementListStatement* statement) {
  LOG_DEBUG("In Statement List")
  statement->statement_list->Accept(this);
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

  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  LOG_DEBUG("lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetLogicStrOp(expression->operation),
            rhs->getType()->getTypeID())

  llvm::LoadInst* load_lhs = builder->CreateLoad(builder->getInt8Ty(), lhs);
  llvm::LoadInst* load_rhs = builder->CreateLoad(builder->getInt8Ty(), rhs);
  llvm::Value* result = nullptr;

  switch(expression->operation) {
    case LogicOperation::OR:
      result = builder->CreateOr(load_lhs, load_rhs, "tmp_or");
      break;

    case LogicOperation::AND:
      result = builder->CreateAnd(load_lhs, load_rhs, "tmp_or");
      break;

    default:
      LOG_CRITICAL("uknown logic op: {}", (int) expression->operation);
  }

  llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt8Ty());
  builder->CreateAlignedStore(result, alloca_result, 1);

  stack.Put(alloca_result);
}

void LLVMIRVisitor::Visit(CompareOpExpression* expression) {
  LOG_DEBUG("In CompOp")

  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  LOG_DEBUG("lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetCompareStrOp(expression->operation),
            rhs->getType()->getTypeID())

  llvm::Value* result = nullptr;

  llvm::Value* casted_lhs = builder->CreateIntCast(builder->CreateAlignedLoad(builder->getInt32Ty(), lhs, 4), builder->getInt32Ty(), true);
  llvm::Value* casted_rhs = builder->CreateIntCast(builder->CreateAlignedLoad(builder->getInt32Ty(), rhs, 4), builder->getInt32Ty(), true);

  switch(expression->operation) {
    case CompareOperation::EQUAL:
      result = builder->CreateICmpEQ(casted_lhs, casted_rhs, "tmp_eq");
      break;

    case CompareOperation::NEQUAL:
      result = builder->CreateICmpNE(casted_lhs, casted_rhs, "tmp_ne");
      break;

    case CompareOperation::LESS:
      result = builder->CreateICmpSLT(casted_lhs, casted_rhs, "tmp_lt");
      break;

    case CompareOperation::GREATER:
      result = builder->CreateICmpSGT(casted_lhs, casted_rhs, "cmp_gt");
      break;

    default:
      LOG_CRITICAL("uknown compare op: {}", (int) expression->operation);
  }

  llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt8Ty());
  builder->CreateStore(builder->CreateIntCast(result, builder->getInt8Ty(), true), alloca_result);

  stack.Put(alloca_result);
}

void LLVMIRVisitor::Visit(MathOpExpression* expression) {
  LOG_DEBUG("In MathOp")

  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  LOG_DEBUG("IN BinOp lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetMathStrOp(expression->operation),
            rhs->getType()->getTypeID());

  llvm::Value* result = nullptr;
  llvm::Value* load_lhs = builder->CreateAlignedLoad(builder->getInt32Ty(), lhs, 4);
  llvm::Value* load_rhs = builder->CreateAlignedLoad(builder->getInt32Ty(), rhs, 4);

  switch(expression->operation) {
    case MathOperation::PLUS:
      result = builder->CreateAdd(load_lhs, load_rhs, "addtmp");
      break;

    case MathOperation::MINUS:
      result = builder->CreateSub(load_lhs, load_rhs, "subtmp");
      break;

    case MathOperation::MUL:
      result = builder->CreateMul(load_lhs, load_rhs, "multmp");
      break;

    case MathOperation::DIV:
      result = builder->CreateSDiv(load_lhs, load_rhs, "divtmp");
      break;

    case MathOperation::PERCENT:
      result = builder->CreateSRem(load_lhs, load_rhs, "tmp_rem");
      break;

    default:
      LOG_CRITICAL("uknown math op: {}", (int) expression->operation);
  }

  llvm::AllocaInst* alloca_result = builder->CreateAlloca(builder->getInt32Ty());
  builder->CreateStore(result, alloca_result);

  stack.Put(alloca_result);
}

void LLVMIRVisitor::Visit(ArrayIdxExpression *expression) {

}

void LLVMIRVisitor::Visit(LengthExpression *expression) {

}

void LLVMIRVisitor::Visit(MethodCallExpression *expression) {

}

void LLVMIRVisitor::Visit(NewArrayExpression *expression) {

}

void LLVMIRVisitor::Visit(NewClassExpression *expression) {

}

void LLVMIRVisitor::Visit(ThisExpression *expression) {

}

void LLVMIRVisitor::Visit(CommaExpressionList *program) {

}

void LLVMIRVisitor::Visit(MethodCall *program) {

}

void LLVMIRVisitor::Visit(AssertStatement *statement) {

}

void LLVMIRVisitor::Visit(MethodCallStatement *statement) {

}

void LLVMIRVisitor::Visit(ArrayLValue *statement) {

}

void LLVMIRVisitor::Visit(FieldLValue *statement) {

}

void LLVMIRVisitor::Visit(IdentifierLValue *statement) {

}

void LLVMIRVisitor::Visit(FieldDeclaration* declaration) {

}

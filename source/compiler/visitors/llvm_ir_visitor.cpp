#include "compiler/core/logger.hpp"

#include "llvm_ir_visitor.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"
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
  llvm::raw_fd_ostream ll("a.ll", error_code);
  module->print(ll, nullptr);
  module->print(llvm::errs(), nullptr);
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
  LOG_DEBUG("In Variable Declaration: int {}", variable_declaration->identifier)

  llvm::Function* function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock& block = function->getEntryBlock();

  // Insert var decl to the beginning
  llvm::IRBuilder<> tmp(&block, block.begin());
  llvm::Value* variable = tmp.CreateAlloca(builder->getInt32Ty(), nullptr, variable_declaration->identifier);
  table.Insert(variable_declaration->identifier, variable);
}

void LLVMIRVisitor::Visit(BinOpExpression* expression) {
  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  llvm::Value* result = nullptr;
  llvm::LoadInst* load_lhs = nullptr;
  llvm::LoadInst* load_rhs = nullptr;

  LOG_DEBUG("IN BinOp lhs_id({}) {} rhs_id({})", lhs->getType()->getTypeID(), GetBinOp(expression->operation),
            rhs->getType()->getTypeID())
  //LOG_DEBUG("lhs_type: {}, rhs_type: {}", (void*) lhs->getType(), (void*) rhs->getType());

  switch(expression->operation) {
    case BinOperation::PLUS:
      load_lhs = builder->CreateLoad(builder->getInt32Ty(), lhs);
      load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
      //llvm::LoadInst* load_rhs = builder->CreateLoad(builder->getInt32Ty(), rhs);
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

      LOG_DEBUG("load_lhs_type: {}, load_rhs_type: {}", (void*) load_lhs->getType(), (void*) load_rhs->getType());
      LOG_DEBUG("load_lhs_type_id: {}, load_rhs_type_id: {}", (void*) load_lhs->getType()->getTypeID(), (void*) load_rhs->getType()->getTypeID());

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

void LLVMIRVisitor::Visit(TrueExpression* expression) {
  LOG_DEBUG("In True Expression")

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  llvm::Value* value = builder->getInt1(true);
  builder->CreateStore(value, alloca);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(FalseExpression* expression) {
  LOG_DEBUG("In False Expression")

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  llvm::Value* value = builder->getInt1(false);
  builder->CreateStore(value, alloca);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(IdentifierExpression* expression) {
  LOG_DEBUG("In Identifier Expression: {}", expression->identifier)
  stack.Put(table.Get(expression->identifier));
}

void LLVMIRVisitor::Visit(IntegerExpression* expression) {
  LOG_DEBUG("In Integer Expression: {}", expression->value)
  /*
  return ConstantFP::get(*TheContext, APFloat(Val));
  
  llvm::ConstantInt::get()
  */

  //stack.Put(llvm::ConstantInt::get(builder->getInt32Ty(), expression->value, true));

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt32Ty());
  llvm::Value* value = builder->getInt32(expression->value);
  builder->CreateStore(value, alloca);

  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
  LOG_DEBUG("In Not Expression")

  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  llvm::Value* true_val = builder->getInt1(true);
  //builder->CreateStore(value, alloca);
  //stack.Put(alloca);
  llvm::Value* val = Accept(expression->expression);

  stack.Put(builder->CreateXor(val, true_val));
}

void LLVMIRVisitor::Visit(AssignmentStatement* statement) {
  LOG_DEBUG("In Assignment Statement: {} = ...", statement->identifier)
  stack.Pop();

  llvm::Value* expr = Accept(statement->expression);
  llvm::LoadInst* load_expr = builder->CreateLoad(builder->getInt32Ty(), expr);
  llvm::Value* var = table.Get(statement->identifier);

  stack.Put(builder->CreateStore(load_expr, var));
}

void LLVMIRVisitor::Visit(IfElseStatement* statement) {
  LOG_DEBUG("In If Statement")
  stack.Pop();

  llvm::Value* cond_value = Accept(statement->cond_expression);

  // Convert condition to a bool by comparing non-equal to 0.0.
  cond_value = builder->CreateICmpEQ(cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  llvm::BasicBlock* then_block  = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block  = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cond_value, then_block, else_block);

  // Emit then value.
  builder->SetInsertPoint(then_block);
  llvm::Value* then_value = Accept(statement->statement_true);
  builder->CreateBr(merge_block);

  // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
  then_block = builder->GetInsertBlock();

  // Emit else block.
  function->getBasicBlockList().push_back(else_block); // emit else block
  builder->SetInsertPoint(else_block);

  llvm::Value* else_value = Accept(statement->statement_false);

  builder->CreateBr(merge_block);
  // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
  else_block = builder->GetInsertBlock();

  // Emit merge block.
  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);
  llvm::PHINode* phi_node = builder->CreatePHI(then_block->getType(), 2, "iftmp");

  phi_node->addIncoming(then_value, then_block);
  phi_node->addIncoming(else_value, else_block);
  stack.Put(phi_node);
}

void LLVMIRVisitor::Visit(IfStatement* statement) {
  LOG_DEBUG("In If Statement")
  stack.Pop();

  llvm::Value* cond_value = Accept(statement->cond_expression);

  // Convert condition to a bool by comparing non-equal to 0.0.
  //cond_value = builder->CreateICmpEQ(cond_value, llvm::ConstantInt::getTrue(*context), "ifcond");

  llvm::Function* function = builder->GetInsertBlock()->getParent();

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  llvm::BasicBlock* then_block  = llvm::BasicBlock::Create(*context, "then", function);
  llvm::BasicBlock* else_block  = llvm::BasicBlock::Create(*context, "else");
  llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(*context, "ifcontinue");

  builder->CreateCondBr(cond_value, then_block, else_block);

  // Emit then value.
  builder->SetInsertPoint(then_block);
  //llvm::Value* then_value = &then_block->back();
  //llvm::Value* then_value = Accept(statement->statement_true);
  llvm::Value* then_value = Accept(statement->statement_true);
  builder->CreateBr(merge_block);

  // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
  then_block = builder->GetInsertBlock();
  // Emit merge block.
  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);

  //llvm::PHINode* phi_node = builder->CreatePHI(llvm::Type::getInt32Ty(*context), 1, "iftmp");
  llvm::PHINode* phi_node = builder->CreatePHI(then_block->getType(), 1, "iftmp");

  phi_node->addIncoming(then_value, then_block);
  stack.Put(phi_node);
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

  llvm::Value* cond_value = Accept(statement->cond_expression);
  // create the new basic block that will be the body of our while statement
  llvm::Function* function = builder->GetInsertBlock()->getParent();

  llvm::BasicBlock* while_body  = llvm::BasicBlock::Create(*context, "while", function);
  llvm::BasicBlock* while_merge  = llvm::BasicBlock::Create(*context, "merge");
  function->getBasicBlockList().push_back(while_merge);
  builder->CreateCondBr(cond_value, while_body, while_merge);

  // and make sure all statements in the while go into our while statement
  builder->SetInsertPoint(while_body);

  // visit the body of the while now
  statement->statement->Accept(this);
  stack.Pop();
  
  /*
    change for non cond jump
  */
  // we now need to conditionally loop back to the body of the while loop if
  // the condition (which we are re-evaluating) is still true, otherwise we
  // branch to the merge point
  llvm::Value* cond_br = builder->CreateCondBr(Accept(statement->cond_expression), while_body, while_merge);

  // and lastly, we want all new statements after the while to go into the
  // merge case
  builder->SetInsertPoint(while_merge);

  stack.Put(cond_br);
}

void LLVMIRVisitor::Visit(StatementList* statement) {
  LOG_DEBUG("In Statement List")
  statement->Accept(this);
}

void LLVMIRVisitor::Visit(LocalVariableStatement* statement) {
  LOG_DEBUG("In Local Var Declaration: int {}", statement->variable_declaration->identifier)
  stack.Pop();

  statement->variable_declaration->Accept(this);
  stack.Put(table.Get(statement->variable_declaration->identifier));
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

}

void LLVMIRVisitor::Visit(CompareOpExpression* expression) {

}

void LLVMIRVisitor::Visit(MathOpExpression* expression) {

}

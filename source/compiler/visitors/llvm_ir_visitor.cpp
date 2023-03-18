#include "compiler/core/logger.hpp"

#include "llvm_ir_visitor.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

void LLVMIRVisitor::TranslateToIR(Program* program, const std::filesystem::path& path) {
  table.Clear();
  stack.Clear();
  InitializeLLVM(path.string());
  Visit(program);
  llvm::verifyModule(*module);
  std::error_code error_code;
  llvm::raw_fd_ostream ll("test.ll", error_code);
  module->print(ll, nullptr);
  module->print(llvm::errs(), nullptr);
  TerminateLLVM();
}

void LLVMIRVisitor::Visit(Program* program) {
  program->main_class->Accept(this);
}

void LLVMIRVisitor::Visit(MainClass* main_class) {
  main_class->statement_list->Accept(this);
}

void LLVMIRVisitor::Visit(ClassDeclaration* class_declaration) {
  //some class stuff
  return;
}

void LLVMIRVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  class_declaration_list->Accept(this);
}

void LLVMIRVisitor::Visit(DeclarationList* declaration_list) {
  declaration_list->Accept(this);
}

void LLVMIRVisitor::Visit(MethodDeclaration* method_declaration) {
  //some class stuff
  return;
}

void LLVMIRVisitor::Visit(VariableDeclaration* variable_declaration) {
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
  switch(expression->operation) {
    case BinOperation::PLUS:
      result = builder->CreateAdd(lhs, rhs, "addtmp");
      break;

    case BinOperation::MINUS:
      result = builder->CreateSub(lhs, rhs, "subtmp");
      break;

    case BinOperation::MUL:
      result = builder->CreateMul(lhs, rhs, "multmp");
      break;

    case BinOperation::DIV:
      result = builder->CreateFDiv(lhs, rhs, "divtmp");
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
      result = builder->CreateICmpSGT(lhs, rhs, "cmp_gt");
      break;

    case BinOperation::OR:
      result = builder->CreateOr(lhs, rhs, "tmp_or");
      break;

    case BinOperation::AND:
      result = builder->CreateAnd(lhs, rhs, "tmp_or");
      break;

    case BinOperation::PERCENT:
      result = builder->CreateSRem(lhs, rhs, "tmp_rem");
      break;

    default: 
      LOG_CRITICAL("uknown binary op: {}", expression->operation);
      break;
  }

  stack.Put(result);
}

void LLVMIRVisitor::Visit(TrueExpression* expression) {
  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  llvm::Value* value = builder->getInt1(true);
  builder->CreateStore(value, alloca);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(FalseExpression* expression) {
  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  llvm::Value* value = builder->getInt1(false);
  builder->CreateStore(value, alloca);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(IdentifierExpression* expression) {
  stack.Put(table.Get(expression->identifier));
}

void LLVMIRVisitor::Visit(IntegerExpression* expression) {
  /*
  return ConstantFP::get(*TheContext, APFloat(Val));
  
  llvm::ConstantInt::get()
  */

  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt32Ty());
  llvm::Value* value = builder->getInt32(expression->value);
  builder->CreateStore(value, alloca);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
  //llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt1Ty());
  llvm::Value* true_val = builder->getInt1(true);
  //builder->CreateStore(value, alloca);
  //stack.Put(alloca);
  llvm::Value* val = Accept(expression->expression);
  stack.Put(builder->CreateXor(val, true_val));
}

void LLVMIRVisitor::Visit(AssignmentStatement* statement) {
  llvm::Value* expr = Accept(statement->expression);
  llvm::LoadInst* load_expr = builder->CreateLoad(builder->getInt32Ty(), expr);
  llvm::Value* var = table.Get(statement->identifier);
  builder->CreateStore(load_expr, var);
}

void LLVMIRVisitor::Visit(IfElseStatement* statement) {
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
  llvm::PHINode* phi_node = builder->CreatePHI(llvm::Type::getInt32Ty(*context), 2, "iftmp");

  phi_node->addIncoming(then_value, then_block);
  phi_node->addIncoming(else_value, else_block);
  stack.Put(phi_node);
}

void LLVMIRVisitor::Visit(IfStatement* statement) {
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
  // Emit merge block.
  function->getBasicBlockList().push_back(merge_block);
  builder->SetInsertPoint(merge_block);
  llvm::PHINode* phi_node = builder->CreatePHI(llvm::Type::getInt32Ty(*context), 1, "iftmp");

  phi_node->addIncoming(then_value, then_block);
  stack.Put(phi_node);
}

void LLVMIRVisitor::Visit(PrintStatement* statement) {
  std::string string = "%d\n";
  llvm::Constant* fmt = llvm::ConstantDataArray::getString(*context, string);

  llvm::AllocaInst* alloca = builder->CreateAlloca(fmt->getType());
  builder->CreateStore(fmt, alloca);

  // cast string to char*
  llvm::Value* formatted_string = builder->CreateBitCast(alloca, builder->getInt8PtrTy());

  llvm::Value* pointer = Accept(statement->expression);

  llvm::LoadInst* value = builder->CreateLoad(builder->getInt32Ty(), pointer);

  llvm::PointerType* pointer_type = builder->getInt8PtrTy();

  llvm::FunctionType* printf_type = llvm::FunctionType::get(
    builder->getInt32Ty(),
    {pointer_type},
    true
  );

  llvm::Function* printf_function = llvm::Function::Create(
    printf_type, llvm::Function::ExternalLinkage,
    "printf",
    *module
  );

  stack.Put(builder->CreateCall(printf_function, {formatted_string, value}, "printCall"));
}

void LLVMIRVisitor::Visit(ReturnStatement* statement) {
  // do fun stuff
  return;
}

void LLVMIRVisitor::Visit(WhileStatement* statement) {
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
  
  /*
    change for non cond jump
  */
  // we now need to conditionally loop back to the body of the while loop if
  // the condition (which we are re-evaluating) is still true, otherwise we
  // branch to the merge point
  builder->CreateCondBr(Accept(statement->cond_expression), while_body, while_merge);

  // and lastly, we want all new statements after the while to go into the
  // merge case
  builder->SetInsertPoint(while_merge);
}

void LLVMIRVisitor::Visit(StatementList* statement) {
  statement->Accept(this);
}

void LLVMIRVisitor::Visit(LocalVariableStatement* statement) {
  statement->variable_declaration->Accept(this);
}

void LLVMIRVisitor::Visit(StatementListStatement* statement) {
  statement->statement_list->Accept(this);
}

llvm::Value* LLVMIRVisitor::Accept(AstNode* ast_node) {
  ast_node->Accept(this);
  return stack.TopAndPop();
}

void LLVMIRVisitor::InitializeLLVM(const std::string& module_name) {
  context = new llvm::LLVMContext();
  module = new llvm::Module(module_name, *context);
  builder = new llvm::IRBuilder<>(*context);
}

void LLVMIRVisitor::TerminateLLVM() {
  delete builder;
  delete module;
  delete context;
}

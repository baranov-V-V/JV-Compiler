#include "compiler/core/logger.hpp"

#include "llvm_ir_visitor.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

void LLVMIRVisitor::TranslateToIR(Program* program) {
  table.Clear();
  stack.Clear();
  InitializeLLVM("file1");
  Visit(program);
  llvm::verifyModule(*module);
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
  llvm::AllocaInst* alloca = builder->CreateAlloca(builder->getInt32Ty());
  llvm::Value* value = builder->getInt32(expression->value);
  builder->CreateStore(value, alloca);
  stack.Put(alloca);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
  builder->CreateFNeg
  //stack.Put(!Accept(expression->expression));
}

void LLVMIRVisitor::Visit(AssignmentStatement* statement) {
  //table.Update(statement->identifier, Accept(statement->expression));
}

void LLVMIRVisitor::Visit(IfElseStatement* statement) {
  /*
  if (Accept(statement->cond_expression)) {
    statement->statement_true->Accept(this);
  } else {
    statement->statement_false->Accept(this);
  }
  */
}

void LLVMIRVisitor::Visit(IfStatement* statement) {
  /*
  if (Accept(statement->cond_expression)) {
    statement->statement_true->Accept(this);
  }
  */
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
  /*
  while (Accept(statement->cond_expression)) {
    statement->statement->Accept(this);
  }
  */
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

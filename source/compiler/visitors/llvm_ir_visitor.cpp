#include "llvm_ir_visitor.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

void LLVMIRVisitor::TranslateToIR(Program* program) {
  table.Clear();
  stack.Clear();
  Visit(program);
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
  /*
  table.Insert(variable_declaration->identifier, 0);
  */
}

void LLVMIRVisitor::Visit(BinOpExpression* expression) {
  /*
  llvm::Value* lhs = Accept(expression->lhs);
  llvm::Value* rhs = Accept(expression->rhs);

  int result = 0;
  switch(expression->operation) {
    case BinOperation::PLUS:        result = lhs +  rhs; break;
    case BinOperation::MINUS:       result = lhs -  rhs; break;
    case BinOperation::MUL:         result = lhs *  rhs; break;
    case BinOperation::DIV:         result = lhs /  rhs; break;
    case BinOperation::EQUAL:       result = lhs == rhs; break;
    case BinOperation::NEQUAL:      result = lhs != rhs; break;
    case BinOperation::LESS:        result = lhs <  rhs; break;
    case BinOperation::GREATER:     result = lhs >  rhs; break;
    case BinOperation::OR:          result = lhs || rhs; break;
    case BinOperation::AND:         result = lhs && rhs; break;
    case BinOperation::PERCENT:     result = lhs %  rhs; break;
    default: break;
  }

  stack.Put(result);
  */
}

void LLVMIRVisitor::Visit(TrueExpression* expression) {
  //stack.Put(1);
}

void LLVMIRVisitor::Visit(FalseExpression* expression) {
  //stack.Put(0);
}

void LLVMIRVisitor::Visit(IdentifierExpression* expression) {
  //stack.Put(table.Get(expression->identifier));
}

void LLVMIRVisitor::Visit(IntegerExpression* expression) {
  //stack.Put(expression->value);
}

void LLVMIRVisitor::Visit(NotExpression* expression) {
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
  /*
  std::cout << Accept(statement->expression) << std::endl;
  */
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

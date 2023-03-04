#include "interpreter.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

int Interpreter::GetResult(Program* program) {
  table.Clear();
  stack.Clear();
  Visit(program);
  return stack.Top();
}

void Interpreter::Visit(ClassDeclaration* class_declaration) {
  //some class stuff
  return;
}

void Interpreter::Visit(MethodDeclaration* method_declaration) {
  //some class stuff
  return;
}

void Interpreter::Visit(VariableDeclaration* variable_declaration) {
  table.Insert(variable_declaration->identifier, 0);
}

void Interpreter::Visit(BinOpExpression* expression) {
  int lhs = Visit(expression->lhs);
  int rhs = Visit(expression->rhs);

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
}

void Interpreter::Visit(TrueExpression* expression) {
  stack.Put(1);
}

void Interpreter::Visit(FalseExpression* expression) {
  stack.Put(0);
}

void Interpreter::Visit(IdentifierExpression* expression) {
  stack.Put(table.Get(expression->identifier));
}

int Interpreter::Visit(AstNode* ast_node) {
  ast_node->Accept(this);
  return stack.TopAndPop();
}

#include "interpreter.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"
#include "compiler/ast/ast.hpp"

#include <iostream>

void Interpreter::Run(Program* program) {
  table.Clear();
  stack.Clear();
  Visit(program);
}

void Interpreter::Visit(Program* program) {
  program->main_class->Accept(this);
}

void Interpreter::Visit(MainClass* main_class) {
  main_class->statement_list->Accept(this);
}

void Interpreter::Visit(ClassDeclaration* class_declaration) {
  //some class stuff
  return;
}

void Interpreter::Visit(ClassDeclarationList* class_declaration_list) {
  class_declaration_list->Accept(this);
}

void Interpreter::Visit(DeclarationList* declaration_list) {
  declaration_list->Accept(this);
}

void Interpreter::Visit(MethodDeclaration* method_declaration) {
  //some class stuff
  return;
}

void Interpreter::Visit(VariableDeclaration* variable_declaration) {
  table.Insert(variable_declaration->identifier, 0);
}

void Interpreter::Visit(BinOpExpression* expression) {
  int lhs = Accept(expression->lhs);
  int rhs = Accept(expression->rhs);

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

void Interpreter::Visit(IntegerExpression* expression) {
  stack.Put(expression->value);
}

void Interpreter::Visit(NotExpression* expression) {
  stack.Put(!Accept(expression->expression));
}

void Interpreter::Visit(AssignmentStatement* statement) {
  table.Update(statement->identifier, Accept(statement->expression));
}

void Interpreter::Visit(IfElseStatement* statement) {
  if (Accept(statement->cond_expression)) {
    statement->statement_true->Accept(this);
  } else {
    statement->statement_false->Accept(this);
  }
}

void Interpreter::Visit(IfStatement* statement) {
  if (Accept(statement->cond_expression)) {
    statement->statement_true->Accept(this);
  }
}

void Interpreter::Visit(PrintStatement* statement) {
  std::cout << Accept(statement->expression) << std::endl;
}

void Interpreter::Visit(ReturnStatement* statement) {
  // do fun stuff
  return;
}

void Interpreter::Visit(WhileStatement* statement) {
  while (Accept(statement->cond_expression)) {
    statement->statement->Accept(this);
  }
}

void Interpreter::Visit(StatementList* statement) {
  statement->Accept(this);
}

void Interpreter::Visit(LocalVariableStatement* statement) {
  statement->variable_declaration->Accept(this);
}

void Interpreter::Visit(StatementListStatement* statement) {
  statement->statement_list->Accept(this);
}

int Interpreter::Accept(AstNode* ast_node) {
  ast_node->Accept(this);
  return stack.TopAndPop();
}

/*
 *   int lhs = Accept(expression->lhs);
  int rhs = Accept(expression->rhs);

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

void Interpreter::Visit(LogicOpExpression* expression) {
  int lhs = Accept(expression->lhs);
  int rhs = Accept(expression->rhs);

  int result = 0;
  switch(expression->operation) {
    case LogicOperation::OR:          result = lhs || rhs; break;
    case LogicOperation::AND:         result = lhs && rhs; break;
    default: break;
  }

  stack.Put(result);
}

void Interpreter::Visit(CompareOpExpression* expression) {
  int lhs = Accept(expression->lhs);
  int rhs = Accept(expression->rhs);

  int result = 0;
  switch(expression->operation) {
    case CompareOperation::EQUAL:       result = lhs == rhs; break;
    case CompareOperation::NEQUAL:      result = lhs != rhs; break;
    case CompareOperation::LESS:        result = lhs <  rhs; break;
    case CompareOperation::GREATER:     result = lhs >  rhs; break;

    default: break;
  }

  stack.Put(result);
}

void Interpreter::Visit(MathOpExpression* expression) {
  int lhs = Accept(expression->lhs);
  int rhs = Accept(expression->rhs);

  int result = 0;
  switch(expression->operation) {
    case MathOperation::PLUS:        result = lhs +  rhs; break;
    case MathOperation::MINUS:       result = lhs -  rhs; break;
    case MathOperation::MUL:         result = lhs *  rhs; break;
    case MathOperation::DIV:         result = lhs /  rhs; break;
    case MathOperation::PERCENT:     result = lhs %  rhs; break;

    default: break;
  }

  stack.Put(result);
}

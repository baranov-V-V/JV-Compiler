#include "while_statement.hpp"

WhileStatement::WhileStatement(Expression* expr, Statement* stmt) :
  cond_expression(expr), statement(stmt) {}

WhileStatement::~WhileStatement() {
  delete cond_expression;
  delete statement;
}

void WhileStatement::Accept(Visitor* visitor) {
  return;
}

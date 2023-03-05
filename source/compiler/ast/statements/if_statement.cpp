#include "if_statement.hpp"

IfStatement::IfStatement(Expression* expr, Statement* stmt) :
  statement_true(stmt), cond_expression(expr) {}

IfStatement::~IfStatement() {
  delete statement_true;
  delete cond_expression;
}

void IfStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

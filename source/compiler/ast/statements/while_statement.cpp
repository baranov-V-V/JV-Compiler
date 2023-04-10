#include "while_statement.hpp"

WhileStatement::WhileStatement(Expression* expr, StatementList* stmt) :
  cond_expression(expr), statement(stmt) {}

WhileStatement::~WhileStatement() {
  delete cond_expression;
  delete statement;
}

void WhileStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

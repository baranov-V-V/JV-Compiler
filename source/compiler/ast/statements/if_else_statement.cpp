#include "if_else_statement.hpp"

IfElseStatement::IfElseStatement(Expression* expr, Statement* statement_true,
                                 Statement* statement_false) :
  cond_expression(expr), statement_true(statement_true), statement_false(statement_false) {}

IfElseStatement::~IfElseStatement() {
  delete cond_expression;
  delete statement_true;
  delete statement_false;
}

void IfElseStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

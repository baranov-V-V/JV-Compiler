#include "assert_statement.hpp"

void AssertStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

AssertStatement::AssertStatement(Expression* expression) : expression(expression) {}

AssertStatement::~AssertStatement() {
  delete expression;
}

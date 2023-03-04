#include "return_statement.hpp"

ReturnStatement::ReturnStatement(Expression* expr) : expression{expr} {}

ReturnStatement::~ReturnStatement() {
  delete expression;
}

void ReturnStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

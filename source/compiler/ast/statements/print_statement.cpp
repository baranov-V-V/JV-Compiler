#include "print_statement.hpp"

PrintStatement::PrintStatement(Expression* expr) :
  expression(expr) {}

PrintStatement::~PrintStatement() {
  delete expression;
}

void PrintStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

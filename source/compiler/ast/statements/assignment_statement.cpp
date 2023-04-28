#include "assignment_statement.hpp"

AssignmentStatement::AssignmentStatement(LValue* value,
                                         Expression* expr) :
  value(value), expression(expr) {}

AssignmentStatement::~AssignmentStatement() {
  delete value;
  delete expression;
}

void AssignmentStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

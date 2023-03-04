#include "assignment_statement.hpp"

AssignmentStatement::AssignmentStatement(const std::string& identifier,
                                         Expression* expr) :
  identifier(identifier), expression(expr) {}

AssignmentStatement::~AssignmentStatement() {
  delete expression;
}

void AssignmentStatement::Accept(Visitor* visitor) {
  return;
}

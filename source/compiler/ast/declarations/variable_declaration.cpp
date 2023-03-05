#include "variable_declaration.hpp"

VariableDeclaration::VariableDeclaration(const std::string& identifier) :
  Declaration(identifier) {}

void VariableDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

#include "variable_declaration.hpp"

VariableDeclaration::VariableDeclaration(SharedPtr<Type> type, const Symbol& identifier) :
  Declaration(identifier), type(std::move(type)) {}

void VariableDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

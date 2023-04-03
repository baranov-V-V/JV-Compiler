#include "field_declaration.hpp"

FieldDeclaration::FieldDeclaration(SharedPtr<Type> type, const Symbol& identifier) :
  type(type), Declaration(identifier) {
}

void FieldDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

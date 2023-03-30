#include "identifier_l_value.hpp"

IdentifierLValue::IdentifierLValue(const Symbol& name) : name(name) {}

void IdentifierLValue::Accept(Visitor* visitor) {
  visitor->visit(this);
}

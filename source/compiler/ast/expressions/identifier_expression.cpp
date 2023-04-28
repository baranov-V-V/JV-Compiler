#include "identifier_expression.hpp"

IdentifierExpression::IdentifierExpression(const Symbol& identifier) :
  identifier(identifier) {}

void IdentifierExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

#include "identifier_expression.hpp"

IdentifierExpression::IdentifierExpression(const std::string& identifier) :
  identifier(identifier) {}

void IdentifierExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

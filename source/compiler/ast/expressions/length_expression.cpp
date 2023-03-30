#include "length_expression.hpp"

LengthExpression::LengthExpression(Expression* identifier) : identifier(identifier) {}

LengthExpression::~LengthExpression() {
  delete identifier;
}

void LengthExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

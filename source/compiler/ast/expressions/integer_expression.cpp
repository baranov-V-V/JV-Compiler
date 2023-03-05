#include "integer_expression.hpp"

IntegerExpression::IntegerExpression(int value) :
  value(value) {}

void IntegerExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

#include "bool_expression.hpp"

void TrueExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

void FalseExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}


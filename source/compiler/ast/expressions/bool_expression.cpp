#include "bool_expression.hpp"

void TrueExpression::Accept(Visitor* visitor) {
  return;
  //visitor->Visit(this->shared_from_this());
}

void FalseExpression::Accept(Visitor* visitor) {
  return;
  //visitor->Visit(this->shared_from_this());
}


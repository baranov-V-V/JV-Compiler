#include "not_expression.hpp"

NotExpression::NotExpression(Expression* expr) : expression(expr) {}

NotExpression::~NotExpression() {
  delete expression;
}

void NotExpression::Accept(Visitor* visitor) {
  return;
}

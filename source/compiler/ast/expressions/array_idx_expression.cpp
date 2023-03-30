

#include "array_idx_expression.hpp"

ArrayIdxExpression::ArrayIdxExpression(Expression* expr, Expression* idx) : expr(expr), idx(idx) {}

ArrayIdxExpression::~ArrayIdxExpression() {
  delete expr;
  delete idx;
}

void ArrayIdxExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

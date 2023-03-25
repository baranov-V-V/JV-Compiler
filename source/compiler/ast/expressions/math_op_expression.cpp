#include "math_op_expression.hpp"

void MathOpExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

MathOpExpression::MathOpExpression(Expression* lhs, MathOperation operation, Expression* rhs) :
  lhs(lhs), rhs(rhs), operation(operation) {}

#include "binary_op_expression.hpp"

BinOpExpression::BinOpExpression(Expression* lhs, BinOperation op,
                                 Expression* rhs) :
  lhs(lhs), rhs(rhs), operation(op) {}

BinOpExpression::~BinOpExpression() {
  delete rhs;
  delete lhs;
}

void BinOpExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
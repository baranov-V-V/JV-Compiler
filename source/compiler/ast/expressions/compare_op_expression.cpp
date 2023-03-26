#include "compare_op_expression.hpp"

CompareOpExpression::CompareOpExpression(Expression* lhs, CompareOperation operation, Expression* rhs) :
lhs(lhs), operation(operation), rhs(rhs) {}

void CompareOpExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

CompareOpExpression::~CompareOpExpression() {
  delete lhs;
  delete rhs;
}

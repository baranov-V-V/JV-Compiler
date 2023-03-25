#include "logic_op_expression.hpp"

LogicOpExpression::LogicOpExpression(Expression* lhs, LogicOperation operation, Expression* rhs) :
  operation(operation), lhs(lhs), rhs(rhs) {}

void LogicOpExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

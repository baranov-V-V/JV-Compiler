#include "method_call_expression.hpp"

void MethodCallExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

MethodCallExpression::MethodCallExpression(MethodCall* call) : call(call) {}

MethodCallExpression::~MethodCallExpression() {
  delete call;
}

#include "method_call.hpp"

void MethodCall::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

MethodCall::MethodCall(const Symbol& functionName, Expression* expr, CommaExpressionList* expressionList)
  : function_name(functionName), caller(expr), expression_list(expressionList) {}

MethodCall::~MethodCall() {
  delete caller;
  delete expression_list;
}

#pragma once

#include "comma_expression_list.hpp"
#include "util/symbol.hpp"

class MethodCall : public AstNode {
 public:
  MethodCall(const Symbol &functionName, Expression *expr, CommaExpressionList *expressionList);
  ~MethodCall() override;

  void Accept(Visitor* visitor) override;

  Symbol function_name;
  Expression* caller;
  CommaExpressionList* expression_list;
};

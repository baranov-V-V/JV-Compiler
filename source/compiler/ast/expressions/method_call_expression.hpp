#pragma once

#include "ast/functional/method_call.hpp"

class MethodCallExpression : public Expression {
 public:
  explicit MethodCallExpression(MethodCall* call);
  ~MethodCallExpression() override;

  void Accept(Visitor* visitor) override;

  MethodCall* call;
};

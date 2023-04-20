#pragma once

#include "ast/functional/method_call.hpp"
#include "ast/statements/statement.hpp"

class MethodCallStatement : public Statement {
 public:
  explicit MethodCallStatement(MethodCall* call);

  ~MethodCallStatement() override;

  void Accept(Visitor* visitor) override;

  MethodCall* call;
};

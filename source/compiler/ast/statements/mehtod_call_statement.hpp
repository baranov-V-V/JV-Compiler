#pragma once

#include "ast/functional/method_call.hpp"
#include "ast/statements/statement.hpp"

class MehtodCallStatement : public Statement {
 public:
  explicit MehtodCallStatement(MethodCall* call);
  ~MehtodCallStatement() override;

  void Accept(Visitor* visitor) override;

  MethodCall* call;
};

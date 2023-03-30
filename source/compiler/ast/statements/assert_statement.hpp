#pragma once

#include "statement.hpp"

class AssertStatement : public Statement {
 public:
  explicit AssertStatement(Expression* expression);
  ~AssertStatement() override;

  void Accept(Visitor* visitor) override;

  Expression* expression;
};

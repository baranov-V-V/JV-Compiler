#pragma once

#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class IntegerExpression : public Expression {
 public:
  explicit IntegerExpression(int value);

  ~IntegerExpression() override = default;

  void Accept(Visitor* visitor) override;

  int value;
};

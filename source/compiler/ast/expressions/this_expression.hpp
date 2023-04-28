#pragma once

#include "expression.hpp"

class ThisExpression : public Expression {
 public:
  ThisExpression() = default;
  ~ThisExpression() override = default;

  void Accept(Visitor* visitor) override;
};

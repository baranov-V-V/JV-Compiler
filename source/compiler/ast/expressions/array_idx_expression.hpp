#pragma once

#include "expression.hpp"

class ArrayIdxExpression : public Expression {
 public:
  ArrayIdxExpression(Expression* expr, Expression* idx);
  ~ArrayIdxExpression() override;

  void Accept(Visitor* visitor) override;

  Expression* expr;
  Expression* idx;
};

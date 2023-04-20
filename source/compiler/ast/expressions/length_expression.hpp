#pragma once

#include "expression.hpp"
#include "util/symbol.hpp"

class LengthExpression : public Expression {
 public:
  explicit LengthExpression(Expression* identifier);

  ~LengthExpression() override;

  void Accept(Visitor* visitor) override;

  Expression* identifier;
};

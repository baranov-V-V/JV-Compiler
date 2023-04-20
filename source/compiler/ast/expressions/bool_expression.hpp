#pragma once

#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class TrueExpression : public Expression {
 public:
  TrueExpression() = default;

  virtual ~TrueExpression() = default;

  void Accept(Visitor* visitor) override;
};

class FalseExpression : public Expression {
 public:
  FalseExpression() = default;

  virtual ~FalseExpression() = default;

  void Accept(Visitor* visitor) override;
};

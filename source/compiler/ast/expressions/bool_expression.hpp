#pragma once

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class TrueExpression: public Expression {
 public:
  TrueExpression() = default;
  virtual ~TrueExpression() = default;
  
  void Accept(Visitor* visitor) override;
};

class FalseExpression: public Expression {
 public:
  FalseExpression() = default;
  virtual ~FalseExpression() = default;
  
  void Accept(Visitor* visitor) override;
};

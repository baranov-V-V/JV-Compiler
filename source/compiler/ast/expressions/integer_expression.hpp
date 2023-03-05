#pragma once

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class IntegerExpression: public Expression { 
 public:
  IntegerExpression(int value);
  virtual ~IntegerExpression() = default;

  virtual void Accept(Visitor* visitor) override;

  int value;
};

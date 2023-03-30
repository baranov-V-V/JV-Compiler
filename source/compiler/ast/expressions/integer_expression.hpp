#pragma once

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class IntegerExpression: public Expression { 
 public:
  explicit IntegerExpression(int value);
  ~IntegerExpression() override = default;

  void Accept(Visitor* visitor) override;

  int value;
};

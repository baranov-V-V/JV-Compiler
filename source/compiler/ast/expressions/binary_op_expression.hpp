#pragma once

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/ast/core/binary_operations.hpp"
#include "compiler/visitors/visitor.hpp"

class BinOpExpression: public Expression {
 public:
  BinOpExpression(Expression* lhs, BinOperation op, Expression* rhs);
  virtual ~BinOpExpression();

  void Accept(Visitor* visitor) override;

  Expression* lhs;
  Expression* rhs;
  BinOperation operation;
};

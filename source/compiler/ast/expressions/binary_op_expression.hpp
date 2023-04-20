#pragma once

#include "ast/expressions/expression.hpp"
#include "ast/core/binary_operations.hpp"
#include "visitors/visitor.hpp"

class [[deprecated]] BinOpExpression : public Expression {
 public:
  BinOpExpression(Expression* lhs, BinOperation op, Expression* rhs);

  ~BinOpExpression() override;

  void Accept(Visitor* visitor) override;

  Expression* lhs;
  Expression* rhs;
  BinOperation operation;
};

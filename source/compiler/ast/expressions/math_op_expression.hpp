#pragma once

#include "ast/core/ast_node.hpp"
#include "ast/expressions/expression.hpp"
#include "ast/core/binary_operations.hpp"

class MathOpExpression : public Expression {
 public:
  MathOpExpression(Expression* lhs, MathOperation operation, Expression* rhs);

  ~MathOpExpression() override;

  void Accept(Visitor* visitor) override;

  Expression* lhs;
  MathOperation operation;
  Expression* rhs;
};
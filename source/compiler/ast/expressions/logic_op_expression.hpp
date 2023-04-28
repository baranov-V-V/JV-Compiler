#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"
#include "ast/core/binary_operations.hpp"

class LogicOpExpression : public Expression {
 public:
  LogicOpExpression(Expression* lhs, LogicOperation operation, Expression* rhs);
  ~LogicOpExpression() override;

  void Accept(Visitor* visitor) override;

  LogicOperation operation;
  Expression* lhs;
  Expression* rhs;
};
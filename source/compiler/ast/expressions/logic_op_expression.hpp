#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"
#include "ast/core/logic_operations.hpp"

class LogicOpExpression : public Expression {
 public:
  LogicOpExpression(Expression* lhs, LogicOperation operation, Expression* rhs);
  ~LogicOpExpression() override = default;

  void Accept(Visitor* visitor) override;

  LogicOperation operation;
  Expression* lhs;
  Expression* rhs;
};
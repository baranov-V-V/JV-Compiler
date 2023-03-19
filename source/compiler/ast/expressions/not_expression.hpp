#pragma once

#include <memory>
#include <string>

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class NotExpression: public Expression {
 public:
  NotExpression(Expression* expr);
  virtual ~NotExpression();

  virtual void Accept(Visitor* visitor) override;

  Expression* expression;
};

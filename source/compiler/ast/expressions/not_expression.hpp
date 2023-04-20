#pragma once

#include <memory>
#include <string>

#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class NotExpression : public Expression {
 public:
  NotExpression(Expression* expr);

  virtual ~NotExpression();

  virtual void Accept(Visitor* visitor) override;

  Expression* expression;
};

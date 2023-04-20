#pragma once

#include "ast/statements/statement.hpp"
#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class ReturnStatement : public Statement {
 public:
  ReturnStatement(Expression* expr);

  virtual ~ReturnStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* expression;
};

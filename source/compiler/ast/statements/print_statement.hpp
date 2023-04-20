#pragma once

#include <iostream>

#include "ast/statements/statement.hpp"
#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class PrintStatement : public Statement {
 public:
  PrintStatement(Expression* expr);

  virtual ~PrintStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* expression;
};

#pragma once

#include <iostream>

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class PrintStatement: public Statement {
 public:
  PrintStatement(Expression* expr);
  virtual ~PrintStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* expression;
};

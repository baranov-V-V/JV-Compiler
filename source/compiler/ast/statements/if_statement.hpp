#pragma once

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class IfStatement: public Statement {
 public:
  IfStatement(Expression* expr, Statement* stmt);
  virtual ~IfStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  Statement* statement_true;
};



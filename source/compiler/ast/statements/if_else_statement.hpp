#pragma once

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class IfElseStatement: public Statement {
 public:
  IfElseStatement(Expression* expr, Statement* statement_true, Statement* statement_false);
  virtual ~IfElseStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  Statement* statement_true;
  Statement* statement_false;
};
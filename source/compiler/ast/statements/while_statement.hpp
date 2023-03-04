#pragma once

#include "compiler/ast/expressions/expression.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/visitors/visitor.hpp"

class WhileStatement: public Statement {
 public:
  WhileStatement(Expression* expr, Statement* stmt);
  virtual ~WhileStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  Statement* statement;
};
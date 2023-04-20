#pragma once

#include "ast/statements/statement.hpp"
#include "ast/statements/statement_list.hpp"
#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class IfStatement : public Statement {
 public:
  IfStatement(Expression* expr, StatementList* stmt);

  virtual ~IfStatement() override;

  virtual void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  StatementList* statement_true;
};



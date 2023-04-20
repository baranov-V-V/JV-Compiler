#pragma once

#include "ast/statements/statement.hpp"
#include "ast/statements/statement_list.hpp"
#include "ast/expressions/expression.hpp"
#include "visitors/visitor.hpp"

class IfElseStatement : public Statement {
 public:
  IfElseStatement(Expression* expr, StatementList* statement_true, StatementList* statement_false);

  ~IfElseStatement() override;

  void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  StatementList* statement_true;
  StatementList* statement_false;
};
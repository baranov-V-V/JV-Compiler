#pragma once

#include "ast/expressions/expression.hpp"
#include "ast/statements/statement_list.hpp"
#include "visitors/visitor.hpp"

class WhileStatement : public Statement {
 public:
  WhileStatement(Expression* expr, StatementList* stmt);

  ~WhileStatement() override;

  void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  StatementList* statement;
};
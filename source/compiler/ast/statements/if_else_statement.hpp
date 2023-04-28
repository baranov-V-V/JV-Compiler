#pragma once

#include "compiler/ast/statements/statement.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/ast/expressions/expression.hpp"
#include "compiler/visitors/visitor.hpp"

class IfElseStatement: public Statement {
 public:
  IfElseStatement(Expression* expr, StatementList* statement_true, StatementList* statement_false);
  ~IfElseStatement() override;

  void Accept(Visitor* visitor) override;

  Expression* cond_expression;
  StatementList* statement_true;
  StatementList* statement_false;
};
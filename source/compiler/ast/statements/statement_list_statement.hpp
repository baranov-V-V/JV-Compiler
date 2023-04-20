#pragma once

#include "ast/core/basic_list.hpp"
#include "ast/statements/statement_list.hpp"
#include "ast/statements/statement.hpp"
#include "visitors/visitor.hpp"

class StatementListStatement : public Statement {
 public:
  explicit StatementListStatement(StatementList* statement_list);

  ~StatementListStatement() override = default;

  void Accept(Visitor* visitor) override;

  StatementList* statement_list;
};
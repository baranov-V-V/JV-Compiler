#pragma once

#include "ast/core/basic_list.hpp"
#include "ast/statements/statement.hpp"
#include "visitors/visitor.hpp"

class StatementList : public BasicList<Statement> {
 public:
  StatementList() = default;

  explicit StatementList(Statement* statement);

  ~StatementList() override = default;

  void Accept(Visitor* visitor) override;
};

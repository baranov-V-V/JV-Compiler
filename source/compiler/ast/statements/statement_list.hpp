#pragma once

#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/visitors/visitor.hpp"

class StatementList: public BasicList<Statement> {
 public:
  StatementList() = default;
  explicit StatementList(Statement* statement);
  ~StatementList() override = default;
  
  void Accept(Visitor* visitor) override;
};

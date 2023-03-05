#pragma once

#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/visitors/visitor.hpp"

class StatementList: public BasicList<Statement> {
 public:
  StatementList() = default;
  StatementList(Statement* statement);
  virtual ~StatementList() = default;
  
  virtual void Accept(Visitor* visitor) override;
};

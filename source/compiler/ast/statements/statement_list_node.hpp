#pragma once

#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/visitors/visitor.hpp"

class StatementListNode: public Statement {
 public:
  StatementListNode(StatementList* statement_list);
  virtual ~StatementListNode() = default;
  
  virtual void Accept(Visitor* visitor) override;

  StatementList* statement_list;
};
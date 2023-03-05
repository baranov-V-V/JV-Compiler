#pragma once

#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/ast/statements/statement.hpp"
#include "compiler/visitors/visitor.hpp"

class StatementListStatement: public Statement {
 public:
  StatementListStatement(StatementList* statement_list);
  virtual ~StatementListStatement() = default;
  
  virtual void Accept(Visitor* visitor) override;

  StatementList* statement_list;
};
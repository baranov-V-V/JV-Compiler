#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/visitors/visitor.hpp"

class MainClass: public AstNode {
 public:
  MainClass(StatementList* statement_list);
  virtual ~MainClass();

  virtual void Accept(Visitor* visitor) override;

  StatementList* statement_list;
};

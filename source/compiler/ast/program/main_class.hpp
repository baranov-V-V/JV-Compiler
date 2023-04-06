#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/statements/statement_list.hpp"
#include "compiler/visitors/visitor.hpp"
#include "types/class_type.hpp"

class MainClass: public AstNode {
 public:
  explicit MainClass(StatementList* statement_list);
  ~MainClass() override;

  void Accept(Visitor* visitor) override;

  StatementList* statement_list;
  SharedPtr<ClassType> type;
};

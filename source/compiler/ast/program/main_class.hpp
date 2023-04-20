#pragma once

#include "ast/core/ast_node.hpp"
#include "ast/statements/statement_list.hpp"
#include "types/class_type.hpp"

class Visitor;

class MainClass : public AstNode {
 public:
  explicit MainClass(StatementList* statement_list);

  ~MainClass() override;

  void Accept(Visitor* visitor) override;

  StatementList* statement_list;
  SharedPtr<ClassType> type;
};

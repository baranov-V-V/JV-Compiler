#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/visitors/visitor.hpp"

class DeclarationList: public BasicList<Declaration> {
 public:
  explicit DeclarationList(Declaration* declaration);
  DeclarationList() = default;
  ~DeclarationList() override = default;

  void Accept(Visitor* visitor) override;
};

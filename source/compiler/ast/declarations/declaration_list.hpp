#pragma once

#include <ast/core/ast_node.hpp>
#include "ast/core/basic_list.hpp"
#include "ast/declarations/declaration.hpp"
#include "visitors/visitor.hpp"

class DeclarationList : public BasicList<Declaration> {
 public:
  explicit DeclarationList(Declaration* declaration);

  DeclarationList() = default;

  ~DeclarationList() override = default;

  void Accept(Visitor* visitor) override;
};

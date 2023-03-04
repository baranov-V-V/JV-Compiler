#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/ast/core/basic_list.hpp"
#include "compiler/ast/declarations/declaration.hpp"
#include "compiler/visitors/visitor.hpp"

class DeclarationList: public BasicList<Declaration> {
 public:
  DeclarationList(Declaration* decaration);
  DeclarationList() = default;

  virtual ~DeclarationList() = default;

  virtual void Accept(Visitor* visitor) override;
};

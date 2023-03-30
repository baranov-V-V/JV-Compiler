#pragma once

#include <string>

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/visitors/visitor.hpp"
#include "util/symbol.hpp"

class Declaration: public AstNode {
 public:
  explicit Declaration(Symbol identifier);
  ~Declaration() override = default;

  void Accept(Visitor* visitor) override = 0;

  Symbol identifier;
};

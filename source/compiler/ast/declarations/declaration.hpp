#pragma once

#include <string>

#include "ast/core/ast_node.hpp"
#include "visitors/visitor.hpp"
#include "util/symbol.hpp"

class Declaration : public AstNode {
 public:
  explicit Declaration(Symbol identifier);

  ~Declaration() override = default;

  void Accept(Visitor* visitor) override = 0;

  Symbol identifier;
};

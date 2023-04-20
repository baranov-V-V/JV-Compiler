#pragma once

#include "ast/core/ast_node.hpp"
#include "visitors/visitor.hpp"

class Statement : virtual public AstNode {
 public:
  void Accept(Visitor* visitor) override = 0;
};

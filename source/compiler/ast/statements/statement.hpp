#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/visitors/visitor.hpp"

class Statement: virtual public AstNode {
 public:
  virtual void Accept(Visitor* visitor) = 0;
};

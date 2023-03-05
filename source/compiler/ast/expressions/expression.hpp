#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/visitors/visitor.hpp"

class Expression: public AstNode {
 public:
  Expression() = default;
  virtual ~Expression() = default;
  
  virtual void Accept(Visitor* visitor) = 0;
};

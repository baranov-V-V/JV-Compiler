#pragma once

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/visitors/visitor.hpp"

class Expression: public AstNode {
 public:
  Expression() = default;
  ~Expression() override = default;
  
  virtual void Accept(Visitor* visitor) override = 0;
};

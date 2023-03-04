#pragma once

#include "compiler/ast/core/binary_operations.hpp"
#include "compiler/visitors/visitor.hpp"

class AstNode {
 public:
  virtual void Accept(Visitor* visitor) = 0;

  virtual ~AstNode() = default;
};

#pragma once

#include "compiler/ast/core/binary_operations.hpp"

class Visitor;

class AstNode {
 public:
  virtual void Accept(Visitor* visitor) = 0;

  virtual ~AstNode() = default;
};

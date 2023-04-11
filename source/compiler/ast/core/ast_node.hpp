#pragma once

#include "compiler/ast/core/binary_operations.hpp"
#include "parser/location.hh"

class Visitor;

class AstNode {
 public:
  AstNode() = default;
  virtual void Accept(Visitor* visitor) = 0;

  virtual ~AstNode() = default;

  yy::location location;
};

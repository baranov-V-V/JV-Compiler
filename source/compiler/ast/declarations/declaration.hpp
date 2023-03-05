#pragma once

#include <string>

#include "compiler/ast/core/ast_node.hpp"
#include "compiler/visitors/visitor.hpp"

class Declaration: public AstNode {
 public:
  Declaration(const std::string& identifier);
  virtual ~Declaration() = default;

  virtual void Accept(Visitor* visitor) = 0;

  std::string identifier;
};

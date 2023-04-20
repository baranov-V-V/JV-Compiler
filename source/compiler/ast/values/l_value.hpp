#pragma once

#include "ast/core/ast_node.hpp"

class LValue : public AstNode {
 public:
  LValue() = default;

  ~LValue() override = default;

  virtual void Accept(Visitor* visitor) override = 0;
};

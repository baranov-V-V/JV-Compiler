#pragma once

#include "compiler/ast/core/ast_node.hpp"

template<typename T>
class VisitorHelper {
 public:
  virtual T Visit(AstNode* ast_node) = 0;
 protected:
  T tos_value;
};
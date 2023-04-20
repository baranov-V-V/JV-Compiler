#pragma once

#include "ast/core/ast_node.hpp"

template<typename T>
class VisitorHelper {
 public:
  virtual T Accept(AstNode* ast_node) = 0;
};
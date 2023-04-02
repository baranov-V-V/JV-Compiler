#pragma once

#include "scope_layer.hpp"

class ClassScopeLayer {

 private:
  std::string name;
  ScopeLayer* parent;
  std::vector<ScopeLayer> children;
  std::unordered_map<Symbol, std::shared_ptr<Object>> variables;

  ScopeLayer* class_scope;
};

#pragma once

#include "scope_layer.hpp"
#include "symbol_layer_tree.hpp"
#include "class_table.hpp"

class SymbolTable {
 public:
  explicit SymbolTable(ScopeLayer* root);
  SymbolTable(SymbolTable&&) = default;
  SymbolTable(const SymbolTable&) = delete;

 private:
  SymbolLayerTree layer_tree;
  ClassTable class_table;
};

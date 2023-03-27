#pragma once

#include <string>
#include <unordered_map>

#include "compiler/core/logger.hpp"
#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"

template <typename Key, typename Val>
class SymbolTable {
 public:
  const Val& Get(const Key& identifier) const;

  void Update(const Key& identifier, const Val& value);

  void Insert(const Key& identifier, const Val& value);

  void Clear();
 private:
  std::unordered_map<Val, Key> table;
};

template<typename Key, typename Val>
const Val& SymbolTable<Key, Val>::Get(const Key& identifier) const {
  if (!table.contains(identifier)) {
    throw UndeclaredVarException(identifier);
  }
  return table.at(identifier);
}

template<typename Key, typename Val>
void SymbolTable<Key, Val>::Update(const Key& identifier, const Val& value) {
  if (!table.contains(identifier)) {
    throw UndeclaredVarException(identifier);
  }
  table.at(identifier) = value;
}

template<typename Key, typename Val>
void SymbolTable<Key, Val>::Insert(const Key& identifier, const Val& value) {
  if (table.contains(identifier)) {
    throw RedeclarationException(identifier);
  }
  table.insert({identifier, value});
}

template<typename Key, typename Val>
void SymbolTable<Key, Val>::Clear() {
  table.clear();
}
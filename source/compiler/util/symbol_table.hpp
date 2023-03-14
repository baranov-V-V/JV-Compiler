#pragma once

#include <string>
#include <unordered_map>

#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"

template <typename T>
class SymbolTable {
 public:
  const T& Get(const std::string& identifier) const;

  void Update(const std::string& identifier, const T& value);

  void Insert(const std::string& identifier, const T& value);

  void Clear();
 private:
  std::unordered_map<std::string, T> table;
};

template <typename T>
const T& SymbolTable<T>::Get(const std::string& identifier) const {
  if (!table.contains(identifier)) {
    throw UndeclaredVarException(identifier);
  }
  return table.at(identifier);
}

template <typename T>
void SymbolTable<T>::Update(const std::string& identifier, const T& value) {
  if (!table.contains(identifier)) {
    throw UndeclaredVarException(identifier);
  }
  table.at(identifier) = value;
}

template <typename T>
void SymbolTable<T>::Insert(const std::string& identifier, const T& value) {
  if (table.contains(identifier)) {
    throw RedeclarationException(identifier);
  }
  table.insert({identifier, value});
}

template <typename T>
void SymbolTable<T>::Clear() {
  table.clear();
}
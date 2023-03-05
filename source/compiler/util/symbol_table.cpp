#include "symbol_table.hpp"

#include "compiler/exceptions/redeclaration_exception.hpp"
#include "compiler/exceptions/undeclared_variable_exception.hpp"

int SymbolTable::Get(const std::string& identifier) const {
  if (!table.contains(identifier)) {
    throw UndeclaredVarException(identifier);
  }
  return table.at(identifier);
}

void SymbolTable::Update(const std::string& identifier, int value) {
  if (!table.contains(identifier)) {
    throw UndeclaredVarException(identifier);
  }
  table.at(identifier) = value;
}

void SymbolTable::Insert(const std::string& identifier, int value) {
  if (table.contains(identifier)) {
    throw RedeclarationException(identifier);
  }
  table.insert({identifier, value});
}

void SymbolTable::Clear() {
  table.clear();
}
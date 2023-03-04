#pragma once

#include <string>
#include <unordered_map>

class SymbolTable {
 public:
  int Get(const std::string& identifier) const;

  void Update(const std::string& identifier, int value);

  void Insert(const std::string& identifier, int value);

  void Clear();
 private:
  std::unordered_map<std::string, int> table;
};
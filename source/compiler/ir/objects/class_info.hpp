#pragma once

#include <vector>
#include <unordered_map>
#include "util/symbol.hpp"
#include "types/method_type.hpp"

class ClassInfo {
 public:
  ClassInfo() = default;
  //ClassInfo(std::initializer_list<SharedPtr<MethodType>> methods, std::initializer_list<SharedPtr<Type>> fields);
  //ClassInfo(const std::vector<SharedPtr<MethodType>>& methods, const std::vector<SharedPtr<Type>>& fields);

  [[nodiscard]] const SharedPtr<MethodType>& GetMethodType(const Symbol& symbol) const;
  [[nodiscard]] bool HasMethodType(const Symbol& symbol) const;
  [[nodiscard]] int GetMethodsNum() const;
  void AddMethodType(const Symbol& symbol, const SharedPtr<MethodType>& method_type);

  [[nodiscard]] const SharedPtr<Type>& GetFieldType(const Symbol& symbol) const;
  [[nodiscard]] bool HasFieldType(const Symbol& symbol) const;
  [[nodiscard]] int GetFieldsNum() const;
  void AddFieldType(const Symbol& symbol, const SharedPtr<Type>& field_type);

  const std::unordered_map<Symbol, SharedPtr<Type>>& GetAllFields();

 private:
  std::unordered_map<Symbol, SharedPtr<MethodType>> methods;
  std::unordered_map<Symbol, SharedPtr<Type>> fields;
};
#pragma once

#include <vector>
#include "util/symbol.hpp"
#include "types/method_type.hpp"

class ClassInfo {
 public:
  ClassInfo() = default;
  ClassInfo(std::initializer_list<SharedPtr<MethodType>> methods, std::initializer_list<SharedPtr<Type>> fields);
  ClassInfo(const std::vector<SharedPtr<MethodType>>& methods, const std::vector<SharedPtr<Type>>& fields);

  [[nodiscard]] const SharedPtr<MethodType>& GetMethodType(int idx) const;
  [[nodiscard]] int GetMethodsNum() const;
  void AddMethodType(const SharedPtr<MethodType>& method_type);

  [[nodiscard]] const SharedPtr<Type>& GetFieldType(int idx) const;
  [[nodiscard]] int GetFieldsNum() const;
  void AddFieldType(const SharedPtr<Type>& field_type);

 private:
  std::vector<SharedPtr<MethodType>> methods;
  std::vector<SharedPtr<Type>> fields;
};
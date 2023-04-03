#pragma once

#include <initializer_list>

#include "type.hpp"
#include "method_type.hpp"


class ClassType : public Type {
 public:
  explicit ClassType(const Symbol& symbol);
  ClassType(const Symbol& symbol, std::initializer_list<SharedPtr<MethodType>> methods, std::initializer_list<SharedPtr<Type>> fields);
  ClassType(const Symbol& symbol, const std::vector<SharedPtr<MethodType>>& methods, const std::vector<SharedPtr<Type>>& fields);

  [[nodiscard]] std::string ToString() const override;

  [[nodiscard]] const SharedPtr<MethodType>& GetMethodType(int idx) const;
  [[nodiscard]] int GetMethodsNum() const;
  void AddMethodType(const SharedPtr<MethodType>& method_type);

  [[nodiscard]] const SharedPtr<Type>& GetFieldType(int idx) const;
  [[nodiscard]] int GetFieldsNum() const;
  void AddFieldType(const SharedPtr<Type>& field_type);

  [[nodiscard]] const Symbol& GetClassName() const;

 private:
  std::vector<SharedPtr<MethodType>> methods;
  std::vector<SharedPtr<Type>> fields;
  Symbol name;
};
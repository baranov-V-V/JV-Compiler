#include "class_info.hpp"

const SharedPtr<MethodType> &ClassInfo::GetMethodType(const Symbol& symbol) const {
  return methods.at(symbol);
}

int ClassInfo::GetMethodsNum() const {
  return methods.size();
}

void ClassInfo::AddMethodType(const Symbol& symbol, const SharedPtr<MethodType>& method_type) {
  methods.insert({symbol, method_type});
}

const SharedPtr<Type> &ClassInfo::GetFieldType(const Symbol& symbol) const {
  return fields.at(symbol);
}

int ClassInfo::GetFieldsNum() const {
  return fields.size();
}

void ClassInfo::AddFieldType(const Symbol& symbol, const SharedPtr<Type> &field_type) {
  fields.insert({symbol, field_type});
}

const std::unordered_map<Symbol, SharedPtr<Type>>& ClassInfo::GetAllFields() {
  return fields;
}

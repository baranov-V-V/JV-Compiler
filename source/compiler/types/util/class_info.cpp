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

/*
const SharedPtr<Type> &ClassInfo::GetFieldType(const Symbol& symbol) const {
  return fields.at(symbol);
}
*/

int ClassInfo::GetFieldsNum() const {
  return fields.size();
}

void ClassInfo::AddFieldType(const Symbol& symbol, const SharedPtr<Type> &field_type) {
  fields.emplace_back(field_type, symbol);
}

const std::vector<TypeEntry>& ClassInfo::GetAllFields() const {
  return fields;
}

bool ClassInfo::HasMethodType(const Symbol& symbol) const {
  return methods.contains(symbol);
}

/*
bool ClassInfo::HasFieldType(const Symbol& symbol) const {
  return fields.contains(symbol);
}
*/

const std::unordered_map<Symbol, SharedPtr<MethodType>>& ClassInfo::GetAllMethods() const {
  return methods;
}

#include "class_type.hpp"

ClassType::ClassType() : Type(Type::TypeID::MethodTy) {}

ClassType::ClassType(std::initializer_list<SharedPtr<MethodType>> methods,
                     std::initializer_list<SharedPtr<Type>> fields) :
                     methods(methods.begin(), methods.end()),
                     fields(fields.begin(), fields.end()),
                     Type(Type::TypeID::MethodTy) {}

ClassType::ClassType(const std::vector<SharedPtr<MethodType>>& methods, const std::vector<SharedPtr<Type>>& fields) :
  methods(methods), fields(fields), Type(Type::TypeID::MethodTy) {}

const SharedPtr<MethodType>& ClassType::GetMethodType(int idx) const {
  return methods.at(idx);
}

int ClassType::GetMethodsNum() const {
  return methods.size();
}

void ClassType::AddMethodType(const SharedPtr<MethodType>& method_type) {
  methods.push_back(method_type);
}

const SharedPtr<Type>& ClassType::GetFieldType(int idx) const {
  return fields.at(idx);
}

int ClassType::GetFieldsNum() const {
  return fields.size();
}

void ClassType::AddFieldType(const SharedPtr<Type>& field_type) {
  fields.push_back(field_type)
}

const Symbol& ClassType::GetClassName() const {
  return name;
}

std::string ClassType::ToString() const {
  return "class \"" + name.name + "\"";
}

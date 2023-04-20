#include "core/logger.hpp"

#include "type_factory.hpp"
#include "core/error.hpp"

SharedPtr<Type> TypeFactory::GetVoidTy() {
  return std::make_shared<Type>(Type::TypeID::VoidTy);
}

SharedPtr<Type> TypeFactory::GetIntTy() {
  return std::make_shared<Type>(Type::TypeID::IntTy);
}

SharedPtr<Type> TypeFactory::GetFloatTy() {
  return std::make_shared<Type>(Type::TypeID::FloatTy);
}

/*
SharedPtr<ClassType> TypeFactory::GetClassTy(std::initializer_list<SharedPtr<MethodType>> methods,
                                             std::initializer_list<SharedPtr<Type>> fields) {
  return std::make_shared<SharedPtr<ClassType>>(methods, fields);
}

SharedPtr<ClassType> TypeFactory::GetClassTy(const std::vector<SharedPtr<MethodType>>& methods,
                                             const std::vector<SharedPtr<Type>>& fields) {
  return std::make_shared<SharedPtr<ClassType>>(methods, fields);
}
*/

SharedPtr<Type> TypeFactory::GetBasicType(const Symbol& literal_type) {
  if (literal_type == "integer" || literal_type == "int") {
    return GetIntTy();
  } else if (literal_type == "float") {
    return GetFloatTy();
  } else if (literal_type == "void") {
    return GetVoidTy();
  }
  //not reachable place
  COMPILER_ERROR("No such basic type [{}] at ", literal_type.name);
}

SharedPtr<Type> TypeFactory::GetBoolTy() {
  return std::make_shared<Type>(Type::TypeID::BoolTy);
}

SharedPtr<ArrayType> TypeFactory::GetArrayTy(const SharedPtr<ClassType>& base_type) {
  return std::make_shared<ArrayType>(base_type);
}

SharedPtr<ArrayType> TypeFactory::GetArrayTy(const SharedPtr<Type>& base_type) {
  return std::make_shared<ArrayType>(base_type);
}

SharedPtr<ClassType> TypeFactory::GetClassTy(const Symbol& class_name) {
  return std::make_shared<ClassType>(class_name);
}

SharedPtr<MethodType>
TypeFactory::GetMethodTy(const Symbol& name, const std::vector<TypeEntry>& args, const SharedPtr<Type>& return_type) {
  return std::make_shared<MethodType>(name, args, return_type);
}

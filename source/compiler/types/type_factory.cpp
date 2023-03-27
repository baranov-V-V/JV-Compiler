#include "type_factory.hpp"

SharedPtr<Type> TypeFactory::GetVoidTy() {
  return SharedPtr<Type>();
}

SharedPtr<Type> TypeFactory::GetIntTy() {
  return SharedPtr<Type>();
}

SharedPtr<Type> TypeFactory::GetFloatTy() {
  return SharedPtr<Type>();
}

SharedPtr<MethodType> TypeFactory::GetMethodTy() {
  return SharedPtr<MethodType>();
}

SharedPtr<ArrayType> TypeFactory::GetArrayTy() {
  return SharedPtr<ArrayType>();
}

SharedPtr<ClassType> TypeFactory::GetClassTy() {
  return SharedPtr<ClassType>();
}

SharedPtr<MethodType> TypeFactory::GetMethodTy(const std::vector<ArgEntry>& args, const SharedPtr<Type>& return_type) {
  return SharedPtr<MethodType>();
}

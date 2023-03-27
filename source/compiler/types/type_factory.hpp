#pragma once

#include "type.hpp"
#include "method_type.hpp"
#include "array_type.hpp"
#include "class_type.hpp"

class TypeFactory {
 public:
  TypeFactory() = delete;
  
  static SharedPtr<Type> GetVoidTy();
  static SharedPtr<Type> GetIntTy();
  static SharedPtr<Type> GetFloatTy();
  static SharedPtr<MethodType> GetMethodTy();
  static SharedPtr<MethodType> GetMethodTy(const std::vector<ArgEntry>& args, const SharedPtr<Type>& return_type);
  static SharedPtr<ArrayType> GetArrayTy();
  static SharedPtr<ClassType> GetClassTy();
};
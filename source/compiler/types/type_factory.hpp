#pragma once

#include "type.hpp"
#include "method_type.hpp"
#include "array_type.hpp"
#include "class_type.hpp"

class TypeFactory {
 public:
  TypeFactory() = delete;

  static SharedPtr<Type> GetBasicType(const Symbol& literal_type);
  static SharedPtr<Type> GetVoidTy();
  static SharedPtr<Type> GetIntTy();
  static SharedPtr<Type> GetBoolTy();
  static SharedPtr<Type> GetFloatTy();
  static SharedPtr<MethodType> GetMethodTy();
  static SharedPtr<MethodType> GetMethodTy(const std::vector<ArgEntry>& args, const SharedPtr<Type>& return_type);
  static SharedPtr<ClassType> GetClassTy(const Symbol& class_name);
  /*
  static SharedPtr<ClassType> GetClassTy(std::initializer_list<SharedPtr<MethodType>> methods,
                                         std::initializer_list<SharedPtr<Type>> fields);
  static SharedPtr<ClassType> GetClassTy(const std::vector<SharedPtr<MethodType>>& methods,
                                         const std::vector<SharedPtr<Type>>& fields);
  */
  static SharedPtr<ArrayType> GetArrayTy(const SharedPtr<ClassType>& base_type);
  static SharedPtr<ArrayType> GetArrayTy(const SharedPtr<Type>& base_type);

 private:
};
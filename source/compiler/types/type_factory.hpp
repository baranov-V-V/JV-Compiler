#pragma once

#include "type.hpp"
#include "method_type.hpp"
#include "array_type.hpp"
#include "class_type.hpp"

class TypeFactory {
 public:
  TypeFactory() = delete;
  
  static Type GetVoidTy();
  static Type GetIntTy();
  static Type GetFloatTy();
  static MethodType GetMethodTy();
  static ArrayType GetArrayTy();
  static ClassType GetClassTy();
};
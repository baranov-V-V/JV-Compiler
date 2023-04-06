#pragma once

#include <memory>
#include "integer.hpp"
#include "method.hpp"
#include "class.hpp"
#include "array.hpp"
#include "bool.hpp"
#include "float.hpp"
#include "types/class_type.hpp"

class ObjectFactory {
 public:
  static std::shared_ptr<Integer> CreateInteger(int value);
  static std::shared_ptr<Float> CreateFloat(float value);
  static std::shared_ptr<Bool> CreateBool(bool value);

  static std::shared_ptr<Object> CreatePrimitive(SharedPtr<Type> type);

  template<class Obj>
  static std::shared_ptr<Array<Obj>> CreateArray(SharedPtr<ArrayType> type, int size);

  static std::shared_ptr<Class> CreateClass(SharedPtr<ClassType> type);

  static std::shared_ptr<Method> CreateMethod(SharedPtr<MethodType> type);
};

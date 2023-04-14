#pragma once

#include <memory>
#include "integer.hpp"
#include "method.hpp"
#include "class_ref.hpp"
#include "array_ref.hpp"
#include "types/class_type.hpp"
#include "bool.hpp"
#include "float.hpp"

class ObjectFactory {
 public:
  static std::shared_ptr<Integer> CreateInteger();

  static std::shared_ptr<Float> CreateFloat();

  static std::shared_ptr<Boolean> CreateBool();

  static std::shared_ptr<IRObject> CreatePrimitive(SharedPtr<Type> type);

  static std::shared_ptr<ArrayRef> CreateArrayRef(SharedPtr<ArrayType> type);
  static std::shared_ptr<ClassRef> CreateClassRef(SharedPtr<ClassType> type);

  static std::shared_ptr<Method> CreateMethod(SharedPtr<MethodType> type);
};

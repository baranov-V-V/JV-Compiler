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
  static std::shared_ptr<Integer> CreateInteger(IRObject::ScopeType scope_type = IRObject::ScopeType::Local);

  static std::shared_ptr<Float> CreateFloat(IRObject::ScopeType scope_type = IRObject::ScopeType::Local);

  static std::shared_ptr<Boolean> CreateBool(IRObject::ScopeType scope_type = IRObject::ScopeType::Local);

  static std::shared_ptr<IRObject>
  CreatePrimitive(SharedPtr<Type> type, IRObject::ScopeType scope_type = IRObject::ScopeType::Local);

  static std::shared_ptr<ArrayRef>
  CreateArrayRef(SharedPtr<ArrayType> type, IRObject::ScopeType scope_type = IRObject::ScopeType::Local);

  static std::shared_ptr<ClassRef>
  CreateClassRef(SharedPtr<ClassType> type, IRObject::ScopeType scope_type = IRObject::ScopeType::Local);

  static std::shared_ptr<Method>
  CreateMethod(SharedPtr<MethodType> type, IRObject::ScopeType scope_type = IRObject::ScopeType::Local);
};

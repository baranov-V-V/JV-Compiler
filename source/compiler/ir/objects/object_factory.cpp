#include "object_factory.hpp"
#include "core/logger.hpp"

std::shared_ptr<Integer> ObjectFactory::CreateInteger(IRObject::ScopeType scope_type) {
  return std::make_shared<Integer>(scope_type);
}

std::shared_ptr<Float> ObjectFactory::CreateFloat(IRObject::ScopeType scope_type) {
  return std::make_shared<Float>(scope_type);
}

std::shared_ptr<Boolean> ObjectFactory::CreateBool(IRObject::ScopeType scope_type) {
  return std::make_shared<Boolean>(scope_type);
}

std::shared_ptr<ClassRef> ObjectFactory::CreateClassRef(SharedPtr<ClassType> type, IRObject::ScopeType scope_type) {
  return std::make_shared<ClassRef>(type, scope_type);
}

std::shared_ptr<IRObject> ObjectFactory::CreatePrimitive(SharedPtr<Type> type, IRObject::ScopeType scope_type) {
  switch (type->GetTypeId()) {
    case Type::TypeID::IntTy:
      return ObjectFactory::CreateInteger(scope_type);

    case Type::TypeID::FloatTy:
      return ObjectFactory::CreateFloat(scope_type);

    case Type::TypeID::BoolTy:
      return ObjectFactory::CreateBool(scope_type);

    default:
      LOG_CRITICAL("Not primitive type {}", type->ToString())
  }
}

std::shared_ptr<ArrayRef> ObjectFactory::CreateArrayRef(SharedPtr<ArrayType> type, IRObject::ScopeType scope_type) {
  return std::make_shared<ArrayRef>(type, scope_type);
}

std::shared_ptr<Method> ObjectFactory::CreateMethod(SharedPtr<MethodType> type, IRObject::ScopeType scope_type) {
  return std::make_shared<Method>(type);
}

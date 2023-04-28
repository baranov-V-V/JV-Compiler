#include "object_factory.hpp"
#include "core/logger.hpp"

std::shared_ptr<Integer> ObjectFactory::CreateInteger() {
  return std::make_shared<Integer>();
}

std::shared_ptr<Float> ObjectFactory::CreateFloat() {
  return std::make_shared<Float>();
}

std::shared_ptr<Boolean> ObjectFactory::CreateBool() {
  return std::make_shared<Boolean>();
}

std::shared_ptr<ClassRef> ObjectFactory::CreateClassRef(SharedPtr<ClassType> type) {
  return std::make_shared<ClassRef>(type);
}

std::shared_ptr<IRObject> ObjectFactory::CreatePrimitive(SharedPtr<Type> type) {
  switch (type->GetTypeId()) {
    case Type::TypeID::IntTy:
      return ObjectFactory::CreateInteger();

    case Type::TypeID::FloatTy:
      return ObjectFactory::CreateFloat();

    case Type::TypeID::BoolTy:
      return ObjectFactory::CreateBool();

    default:
      LOG_CRITICAL("Not primitive type {}", type->ToString())
  }
}

std::shared_ptr<ArrayRef> ObjectFactory::CreateArrayRef(SharedPtr<ArrayType> type) {
  return std::make_shared<ArrayRef>(type);
}

std::shared_ptr<Method> ObjectFactory::CreateMethod(SharedPtr<MethodType> type) {
  return std::make_shared<Method>(type);
}

#include "object_factory.hpp"

std::shared_ptr<Integer> ObjectFactory::CreateInteger(int value) {
  return std::make_shared<Integer>();
}

std::shared_ptr<Float> ObjectFactory::CreateFloat(float value) {
  return std::shared_ptr<Float>();
}

std::shared_ptr<Bool> ObjectFactory::CreateBool(bool value) {
  return std::shared_ptr<Bool>();
}

std::shared_ptr<Class> ObjectFactory::CreateClass(SharedPtr<ClassType> type) {
  return std::shared_ptr<Class>();
}

std::shared_ptr<Method> ObjectFactory::CreateMethod(SharedPtr<MethodType> type) {
  return std::shared_ptr<Method>();
}
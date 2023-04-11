#include "method.hpp"

SharedPtr<Type> Method::GetType() const {
  return type;
}

std::string Method::ToString() const {
  return "Method " + type->ToString();
}

bool Method::Equals(const Object* obj) {
  return false;
}

Method::Method(const SharedPtr<MethodType>& type) : type(type) {}

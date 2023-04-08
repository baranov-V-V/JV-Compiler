#include "class_ref.hpp"

ClassRef::ClassRef(const SharedPtr<ClassType>& type) : type(type) {}

SharedPtr<Type> ClassRef::GetType() const {
  return type;
}

std::string ClassRef::ToString() const {
  return type->ToString() + "&";
}

bool ClassRef::Equals(const Object* obj) {
  //TODO(make equals)
  return false;
}

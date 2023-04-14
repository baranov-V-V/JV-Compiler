#include "array_ref.hpp"

SharedPtr<Type> ArrayRef::GetType() const {
  return type;
}

std::string ArrayRef::ToString() const {
  return type->ToString() + "&";
}

bool ArrayRef::Equals(const IRObject* obj) {
  //TODO(make equals)
  return false;
}

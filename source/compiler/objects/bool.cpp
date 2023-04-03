#include "bool.hpp"
#include "types/type_factory.hpp"

Bool::Bool(bool value) : value(value) {}

SharedPtr<Type> Bool::GetType() const {
  return TypeFactory::GetBoolTy();
}

std::string Bool::ToString() const {
  return TypeFactory::GetBoolTy()->ToString() + (value ? " true" : " false");
}

bool Bool::Equals(const Object* obj) {
  return false;
}

bool Bool::GetValue() const {
  return value;
}

void Bool::SetValue(bool value) {
  Bool::value = value;
}

#include "bool.hpp"
#include "types/type_factory.hpp"

Boolean::Boolean(bool value) : value(value) {}

SharedPtr<Type> Boolean::GetType() const {
  return TypeFactory::GetBoolTy();
}

std::string Boolean::ToString() const {
  return TypeFactory::GetBoolTy()->ToString() + (value ? " true" : " false");
}

bool Boolean::Equals(const IRObject* obj) {
  //TODO(make equals)
  return false;
}

bool Boolean::GetValue() const {
  return value;
}

void Boolean::SetValue(bool value) {
  Boolean::value = value;
}

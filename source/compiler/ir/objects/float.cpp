#include "float.hpp"
#include "types/type_factory.hpp"

Float::Float(float value) : value(value) {}

SharedPtr<Type> Float::GetType() const {
  return TypeFactory::GetFloatTy();
}

std::string Float::ToString() const {
  return TypeFactory::GetFloatTy()->ToString() + std::to_string(value);
}

bool Float::Equals(const Object* obj) {
  return false;
}

float Float::GetValue() const {
  return value;
}

void Float::SetValue(float value) {
  Float::value = value;
}


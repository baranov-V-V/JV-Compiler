#include "integer.hpp"
#include "types/type_factory.hpp"

Integer::Integer(int value) : value(value) {}

SharedPtr<Type> Integer::GetType() const {
  return TypeFactory::GetIntTy();
}

std::string Integer::ToString() const {
  return TypeFactory::GetIntTy()->ToString() + std::to_string(value);
}

bool Integer::Equals(const Object* obj) {
  if (obj->GetType() != this->GetType()) {
    return false;
  }
  Integer* casted_obj = (Integer*) obj;
  return casted_obj->value == this->value;
}

int Integer::GetValue() const {
  return value;
}

void Integer::SetValue(int value) {
  Integer::value = value;
}

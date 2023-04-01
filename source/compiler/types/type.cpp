#include "type.hpp"

bool Type::IsInteger() const {
  return id == TypeID::IntTy;
}

bool Type::IsClass() const {
  return id == TypeID::ClassTy;
}

bool Type::IsArray() const {
  return id == TypeID::ArrayTy;
}

bool Type::operator==(const Type& other) const {
  return id == other.id;
}

bool Type::operator!=(const Type& other) const {
  return id != other.id;
}

Type::Type(Type::TypeID id) : id(id) {}

Type::TypeID Type::GetTypeId() const {
  return id;
}

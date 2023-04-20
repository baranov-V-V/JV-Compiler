#include "core/logger.hpp"
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

Type::Type(Type::TypeID id) : id(id) {}

Type::TypeID Type::GetTypeId() const {
  return id;
}

std::string Type::ToString() const {
  switch (id) {
    case TypeID::IntTy:
      return "int";

    case TypeID::VoidTy:
      return "void";

    case TypeID::FloatTy:
      return "float";

    case TypeID::BoolTy:
      return "bool";

    default:
    LOG_CRITICAL("Unknown basic type [{}]", (int) id)
  }
}

bool Type::Equals(std::shared_ptr<Type> other) {
  return id == other->GetTypeId();
}

bool Type::IsPrimitive() const {
  //LOG_DEBUG("type_id: {}", (int) id)
  return !IsArray() && !IsClass() && !IsMethod() && (id != TypeID::VoidTy);
}

bool Type::IsMethod() const {
  return id == TypeID::MethodTy;
}

bool Type::IsVoid() const {
  return id == TypeID::VoidTy;
}

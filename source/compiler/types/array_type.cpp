#include "array_type.hpp"

ArrayType::ArrayType(const SharedPtr<Type>& elem_type) :
  Type(Type::TypeID::ArrayTy), elem_type(elem_type) {}

ArrayType::ArrayType() : Type(Type::TypeID::ArrayTy) {}

const SharedPtr<Type>& ArrayType::GetElemType() const {
  return elem_type;
}

std::string ArrayType::ToString() const {
  return elem_type->ToString() + "[]";
}

bool ArrayType::Equals(std::shared_ptr<Type> other) {
  if (other->GetTypeId() != TypeID::ArrayTy) {
    return false;
  }
  SharedPtr<ArrayType> casted_other = std::reinterpret_pointer_cast<ArrayType>(other);

  return elem_type->Equals(casted_other->elem_type);
}

#include "array_type.hpp"

ArrayType::ArrayType(const SharedPtr<Type>& elem_type) :
  Type(Type::TypeID::ArrayTy), elem_type(elem_type) {}

ArrayType::ArrayType() : Type(Type::TypeID::ArrayTy) {}

const SharedPtr<Type>& ArrayType::GetElemType() const {
  return elem_type;
}

bool ArrayType::operator==(const ArrayType& rhs) const {
  return static_cast<const Type&>(*this) == static_cast<const Type&>(rhs) &&
         elem_type == rhs.elem_type;
}

bool ArrayType::operator!=(const ArrayType& rhs) const {
  return !(rhs == *this);
}

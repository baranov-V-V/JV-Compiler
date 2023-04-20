#include "naive_type_converter.hpp"
#include "types/type_factory.hpp"

bool NaiveTypeConverter::IsConvertable(SharedPtr<Type> to, SharedPtr<Type> from) {
  if (to->Equals(from)) {
    return true;
  }

  if (!to->IsPrimitive() || !from->IsPrimitive()) {
    return false;
  }

  return (from->GetTypeId() == Type::TypeID::BoolTy);
}

bool NaiveTypeConverter::IsNarrowingConvertable(SharedPtr<Type> to, SharedPtr<Type> from) {
  if (IsConvertable(to, from)) {
    return true;
  }

  if (from->GetTypeId() == Type::TypeID::BoolTy) {
    return true;
  }

  return (to->GetTypeId() == Type::TypeID::IntTy && from->GetTypeId() == Type::TypeID::FloatTy) ||
         (from->GetTypeId() == Type::TypeID::IntTy && to->GetTypeId() == Type::TypeID::FloatTy) ||
         to->GetTypeId() == Type::TypeID::BoolTy;
}

SharedPtr<Type> NaiveTypeConverter::CommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs) {
  if (lhs->Equals(rhs)) {
    return lhs;
  }

  if (lhs->GetTypeId() == Type::TypeID::FloatTy || rhs->GetTypeId() == Type::TypeID::FloatTy) {
    return TypeFactory::GetFloatTy();
  }

  if (lhs->GetTypeId() == Type::TypeID::IntTy || rhs->GetTypeId() == Type::TypeID::IntTy) {
    return TypeFactory::GetIntTy();
  }

  return TypeFactory::GetBoolTy();
}

bool NaiveTypeConverter::HasCommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs) {
  if (lhs->Equals(rhs)) {
    return true;
  };

  return IsNarrowingConvertable(lhs, rhs) || IsNarrowingConvertable(rhs, lhs);
}

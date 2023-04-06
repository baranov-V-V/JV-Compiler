#pragma once

#include "types/type.hpp"

class TypeConverter {
 public:
  TypeConverter() = default;
  virtual ~TypeConverter() = default;

  virtual bool IsConvertable(SharedPtr<Type> to, SharedPtr<Type> from) = 0;
  virtual bool IsNarrowingConvertable(SharedPtr<Type> to, SharedPtr<Type> from) = 0;

  virtual bool HasCommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs) = 0;
  virtual SharedPtr<Type> CommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs) = 0;
};


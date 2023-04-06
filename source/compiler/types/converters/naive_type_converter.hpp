#pragma once

#include "type_converter.hpp"

class NaiveTypeConverter : TypeConverter {
 public:
  NaiveTypeConverter() = default;
  ~NaiveTypeConverter() override = default;

  bool IsConvertable(SharedPtr<Type> to, SharedPtr<Type> from) override;
  bool IsNarrowingConvertable(SharedPtr<Type> to, SharedPtr<Type> from) override;

  bool HasCommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs) override;
  SharedPtr<Type> CommonType(SharedPtr<Type> lhs, SharedPtr<Type> rhs) override;
};

#pragma once

#include "type.hpp"

class ArrayType : public Type {
 public:
  ArrayType();
  explicit ArrayType(const SharedPtr<Type>& elem_type);

  [[nodiscard]] const SharedPtr<Type>& GetElemType() const;

  bool operator==(const ArrayType& rhs) const;
  bool operator!=(const ArrayType& rhs) const;

 private:
  SharedPtr<Type> elem_type;
};
#pragma once

#include "type.hpp"

class ArrayType : public Type {
 public:
  ArrayType();

  explicit ArrayType(const SharedPtr<Type>& elem_type);

  [[nodiscard]] const SharedPtr<Type>& GetElemType() const;

  [[nodiscard]] std::string ToString() const override;

  bool Equals(std::shared_ptr<Type> other) override;

 private:
  SharedPtr<Type> elem_type;
};
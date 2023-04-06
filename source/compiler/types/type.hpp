#pragma once

#include <memory>

class Type {
 public:
  enum class TypeID {
    VoidTy = 0,
    IntTy,
    BoolTy,
    FloatTy,
    ClassTy,
    ArrayTy,
    MethodTy,
  };

  [[nodiscard]] TypeID GetTypeId() const;
  [[nodiscard]] virtual std::string ToString() const;

  explicit Type(TypeID id);

  [[nodiscard]] bool IsInteger() const;
  [[nodiscard]] bool IsPrimitive() const;
  [[nodiscard]] bool IsClass() const;
  [[nodiscard]] bool IsArray() const;
  [[nodiscard]] bool IsMethod() const;

  virtual bool Equals(std::shared_ptr<Type> other);

 private:
  TypeID id;
};

template <typename Type>
using SharedPtr = std::shared_ptr<Type>;
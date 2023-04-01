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

  explicit Type(TypeID id);

  [[nodiscard]] bool IsInteger() const;
  [[nodiscard]] bool IsClass() const;
  [[nodiscard]] bool IsArray() const;

  bool operator==(const Type& other) const;
  bool operator!=(const Type& other) const;

 private:
  TypeID id;
};

template <typename Type>
using SharedPtr = std::shared_ptr<Type>;
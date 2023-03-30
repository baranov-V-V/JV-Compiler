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

  explicit Type(TypeID id);

  bool IsInteger() const;
  bool IsClass() const;
  bool IsArray() const;

  bool operator==(const Type& other) const;
  bool operator!=(const Type& other) const;

 private:
  TypeID id;
};

template <typename Type>
using SharedPtr = std::shared_ptr<Type>;
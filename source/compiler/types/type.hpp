#pragma once

class Type {
 public:
  Type() = default;

  Type(const Type&) = delete;
  Type operator=(const Type&) = delete;

  Type(Type&&) = default;

  bool IsInteger() const;
  bool IsClass() const;
  bool IsArray() const;

  enum TypeID {
    VoidTy = 0,
    IntTy,
    FloatTy,
    ClassTy,
    ArrayTy,
    MethodTy,
  };

  bool operator==(const Type& other) const;
  bool operator!=(const Type& other) const;

 private:
  TypeID id;
};

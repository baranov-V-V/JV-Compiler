#pragma once

#include <unordered_map>
#include <vector>

#include "ir_object.hpp"
#include "types/array_type.hpp"

class ArrayRef : public IRObject {
 public:
  explicit ArrayRef(const SharedPtr<ArrayType>& type) : type(type) {}

  ~ArrayRef() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;

  bool Equals(const IRObject* obj) override;

 private:
  SharedPtr<ArrayType> type;
  //llvm::value* array;
  //std::vector<Obj> objects;
};

/*
template<typename Obj>
std::string ArrayRef<Obj>::ToString() const {
  std::string res = type->ToString() + " {";
  for (const Obj& obj: objects) {
    res += obj->ToString() + ", ";
  }
  res += "}";
  return res;
}
*/

/*
template<typename Obj>
bool ArrayRef<Obj>::Equals(const IRObject* obj) {
  assert(!"not implemented");
  return true;
  /*if (!obj->GetType()->IsArray()) {
    return false;
  }
  ArrayRef<Obj>* array = (ArrayRef<Obj>*)obj;
}
*/
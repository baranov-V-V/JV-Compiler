#pragma once

#include <unordered_map>
#include <vector>

#include "object.hpp"
#include "types/array_type.hpp"

template <typename  Obj>
class Array : public Object {
 public:

  [[nodiscard]] SharedPtr<Type> GetType() const override;

  [[nodiscard]] std::string ToString() const override;

  bool Equals(const Object* obj) override;

 private:
  SharedPtr<ArrayType> type;
  std::vector<Obj> objects;
};

template<typename Obj>
SharedPtr<Type> Array<Obj>::GetType() const {
  return SharedPtr<Type>();
}

template<typename Obj>
std::string Array<Obj>::ToString() const {
  return "array[]";
}

template<typename Obj>
bool Array<Obj>::Equals(const Object* obj) {
  if (!obj->GetType()->IsArray()) {
    return false;
  }
  Array<Obj>* array = (Array<Obj>*)obj;
}

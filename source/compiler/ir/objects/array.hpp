#pragma once

#include <unordered_map>
#include <vector>

#include "object.hpp"
#include "types/array_type.hpp"

template <typename  Obj>
class Array : public Object {
 public:
  Array(int size, const SharedPtr<ArrayType>& type) : size(size), type(type) {}

  ~Array() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;

  [[nodiscard]] int GetSize() const;

  bool Equals(const Object* obj) override;

  [[nodiscard]]       Obj& Get(int idx);
  [[nodiscard]] const Obj& Get(int idx) const;

 private:
  int size;
  SharedPtr<ArrayType> type;
  std::vector<Obj> objects;
};

template<typename Obj>
int Array<Obj>::GetSize() const {
  return size;
}

template<typename Obj>
Obj& Array<Obj>::Get(int idx) {
  return objects.at(idx);
}

template<typename Obj>
const Obj& Array<Obj>::Get(int idx) const {
  return objects.at(idx);
}

template<typename Obj>
SharedPtr<Type> Array<Obj>::GetType() const {
  return type;
}

template<typename Obj>
std::string Array<Obj>::ToString() const {
  std::string res = type->ToString() + " {";
  for (const Obj& obj: objects) {
    res += obj->ToString() + ", ";
  }
  res += "}";
  return res;
}

template<typename Obj>
bool Array<Obj>::Equals(const Object* obj) {
  return true;
  /*if (!obj->GetType()->IsArray()) {
    return false;
  }
  Array<Obj>* array = (Array<Obj>*)obj;
  */
}

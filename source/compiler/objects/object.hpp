#pragma once

#include <string>

#include "compiler/types/type.hpp"

class Object {
 public:
  Object() = default;
  virtual ~Object() = default;

  [[nodiscard]] virtual SharedPtr<Type> GetType() const = 0;
  [[nodiscard]] virtual std::string ToString() const = 0;

  [[nodiscard]] virtual bool Equals(const Object* obj) = 0;

  //virtual bool ToBool() const;

  //virtual int ToInt() const;

  //virtual bool IsClass() const;
  //bool IsArray() const;

  //void SetArray(bool is_array);

  //virtual void Print(std::ostream& stream) const;
};

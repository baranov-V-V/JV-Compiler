#pragma once

#include <string>

#include "compiler/types/type.hpp"

class Object {
  Object(Type type);
  virtual ~Object() = default;

  Type GetType() const;
  virtual std::string ToString() const = 0;
  virtual void Equals(const Object* obj) = 0;

  //virtual bool ToBool() const;

  //virtual int ToInt() const;

  //virtual bool IsClass() const;
  //bool IsArray() const;

  //void SetArray(bool is_array);

  //virtual void Print(std::ostream& stream) const;

 protected:
  Type type;
};

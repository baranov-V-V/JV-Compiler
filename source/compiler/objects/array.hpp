#pragma once

#include <unordered_map>
#include "types/core/object.hpp"

class Array : public Object {
 public:


  std::string ToString() const override;
  void Equals(const Object* obj) override;

 private:
  std::unordered_map<std::string, >
};

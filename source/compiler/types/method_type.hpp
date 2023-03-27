#pragma once

#include <vector>

#include "type.hpp"

class MethodType : public Type {
 public:
  MethodType();

  int GetArgsNum() const;
  Type GetReturnType() const;

 private:
  
  std::vector<Type> arg_types;
  std::vector<Symbol> arg_names;

  bool is_main = false;
};
#pragma once

#include <string>
#include "compiler/parser/location.hh"

class Symbol {
 public:
  explicit Symbol(const std::string& name);
  Symbol(const std::string& name, yy::location location);

  bool operator==(const Symbol& other) const;
  bool operator!=(const Symbol& other) const;

  bool operator==(const std::string& other) const;
  bool operator!=(const std::string& other) const;

  std::string name;
  yy::location location;
};

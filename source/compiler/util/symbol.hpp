#pragma once

#include <string>
#include "compiler/parser/location.hh"

class Symbol {
 public:
  Symbol(const std::string& name, yy::location location);

  bool operator==(const Symbol& other) const;
  bool operator!=(const Symbol& other) const;

  bool operator==(const std::string& other) const;
  bool operator!=(const std::string& other) const;

  [[nodiscard]] const std::string& GetName() const;

 private:
  std::string name;
  yy::location location;
};

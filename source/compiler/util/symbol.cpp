#include "symbol.hpp"

Symbol::Symbol(const std::string& name, yy::location location) : name(name), location(location) {}

bool Symbol::operator==(const Symbol& other) const {
  return name == other.name;
}

bool Symbol::operator!=(const Symbol& other) const {
  return name != other.name;
}

const std::string& Symbol::GetName() const {
  return name;
}

bool Symbol::operator!=(const std::string& other) const {
  return name == other;
}

bool Symbol::operator==(const std::string& other) const {
  return name == other;
}

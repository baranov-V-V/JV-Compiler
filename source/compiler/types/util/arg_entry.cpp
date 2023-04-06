#include "util/symbol.hpp"
#include "arg_entry.hpp"

ArgEntry::ArgEntry(const SharedPtr<Type>& type, const Symbol& symbol) : type(type), symbol(symbol) {}

bool ArgEntry::operator==(const ArgEntry& rhs) const {
  return type->Equals(rhs.type);
}

bool ArgEntry::operator!=(const ArgEntry& rhs) const {
  return !(rhs == *this);
}

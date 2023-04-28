#include "util/symbol.hpp"
#include "type_entry.hpp"

TypeEntry::TypeEntry(const SharedPtr<Type>& type, const Symbol& symbol) : type(type), symbol(symbol) {}

bool TypeEntry::operator==(const TypeEntry& rhs) const {
  return type->Equals(rhs.type);
}

bool TypeEntry::operator!=(const TypeEntry& rhs) const {
  return !(rhs == *this);
}

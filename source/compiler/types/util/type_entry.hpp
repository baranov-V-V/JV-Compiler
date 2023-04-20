#pragma once

#include <memory>
#include "types/type.hpp"
#include "util/symbol.hpp"

class TypeEntry {
 public:
  TypeEntry() = default;

  TypeEntry(const SharedPtr<Type>& type, const Symbol& symbol);

  bool operator==(const TypeEntry& rhs) const;

  bool operator!=(const TypeEntry& rhs) const;

  SharedPtr<Type> type;
  Symbol symbol;
};
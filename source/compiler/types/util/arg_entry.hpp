#pragma once

#include <memory>
#include "types/type.hpp"
#include "util/symbol.hpp"

class ArgEntry {
 public:
  ArgEntry(const SharedPtr<Type>& type, const Symbol& symbol);

  bool operator==(const ArgEntry& rhs) const;
  bool operator!=(const ArgEntry& rhs) const;

  SharedPtr<Type> type;
  Symbol symbol;
};
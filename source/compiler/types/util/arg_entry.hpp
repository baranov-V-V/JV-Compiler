#pragma once

#include <memory>
#include "types/type.hpp"
#include "util/symbol.hpp"

class ArgEntry {
 public:
  ArgEntry(const SharedPtr<Type>& type, const Symbol& symbol);

  SharedPtr<Type> type;
  Symbol symbol;
};
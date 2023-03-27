#include "util/symbol.hpp"
#include "arg_entry.hpp"

ArgEntry::ArgEntry(const SharedPtr<Type>& type, const Symbol& symbol) : type(type), symbol(symbol) {}

#include "declaration.hpp"

#include <utility>

Declaration::Declaration(Symbol identifier) :
  identifier(std::move(identifier)) {}
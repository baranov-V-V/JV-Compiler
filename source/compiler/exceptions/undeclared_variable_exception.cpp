#include "undeclared_variable_exception.hpp"

UndeclaredVarException::UndeclaredVarException(
  const std::string& variable_info) :
  what_string("\'" + variable_info + "\' was not declared in this scope") {}

const char* UndeclaredVarException::what() const noexcept {
  return what_string.c_str();
}

#include "redeclaration_exception.hpp"

//#include <format>
//no format lib :(()

RedeclarationException::RedeclarationException(
  const std::string& variable_info) :
  what_string("redecalration of \'" + variable_info + "\'")  {}

const char* RedeclarationException::what() const noexcept {
  return what_string.c_str();
}

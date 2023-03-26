#include "compilation_exception.hpp"

const char* CompilationException::what() const noexcept {
  return "general compilation error, explanatory message should be printed in advance";
}

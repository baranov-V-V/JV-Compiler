#include "core/logger.hpp"

#include <fstream>

#include "exceptions/compilation_exception.hpp"
#include "parser/driver.hpp"
#include "core/compiler.hpp"

int main(int argc, const char* argv[]) {
  Compiler compiler;

  try {
    compiler.Compile(argc, argv);
  } catch (const CompilationException& e) {
    LOG_TRACE("compilation error occurred")
  }

  return 0;
}
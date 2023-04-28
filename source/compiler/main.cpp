#include "compiler/core/logger.hpp"

#include <fstream>

#include "compiler/exceptions/compilation_exception.hpp"
#include "compiler/parser/driver.hpp"
#include "compiler/core/compiler.hpp"

int main(int argc, char** argv) {
  Compiler compiler;

  try {
    compiler.Compile(argc, argv);
  } catch (const CompilationException& e) {
    LOG_TRACE("compilation error occurred")
  }

  return 0;
}
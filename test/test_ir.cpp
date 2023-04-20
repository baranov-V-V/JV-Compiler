#include "gtest/gtest.h"
#include "core/compiler.hpp"
#include "core/logger.hpp"
#include "exceptions/compilation_exception.hpp"


TEST(a, a) {
  Compiler compiler;

  char* p_string[] = {
    "aa",
    "bb"
  };

  ASSERT_EQ(1, 2);

  /*
  try {
    compiler.Compile(2, p_string);
  } catch (const CompilationException& e) {
    LOG_TRACE("compilation error occurred")
  }
  */
}
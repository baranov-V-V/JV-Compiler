#include "gtest/gtest.h"
#include "core/compiler.hpp"

TEST(a, a) {
  Compiler compiler;

  char* p_string[] = {
    "aa",
    "bb"
  };

  ASSERT_EQ(2, 2);

  //ASSERT_ANY_THROW()
  /*
  try {
    compiler.Compile(2, p_string);
  } catch (const CompilationException& e) {
    LOG_TRACE("compilation error occurred")
  }
  */
}
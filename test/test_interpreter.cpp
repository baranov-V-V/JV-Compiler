#include "gtest/gtest.h"
#include "scn/scn.h"

#include "core/compiler.hpp"
#include "fixtures/compiler_fixture.hpp"

#include <deque>

TEST_F(TestCompiledProgram, simple) {
  test_path.append("primitive").append("test1").replace_extension("jv");

  int a;
  
  CompileProgram();
  OutputBuffer buffer(ExecuteProgram());
  
  auto result = scn::scan(scn::string_view{buffer.Data()}, "{}\n", a);
  
  ASSERT_TRUE(result.empty()) << "left is: [" << result.range_as_string() << "]\n";
  ASSERT_EQ(a, 5);
}

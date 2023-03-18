#include "gtest/gtest.h"

#include "fmt/core.h"
#include "fmt/printf.h"

TEST(Hello_world, simple) {
  fmt::print("Hello world {}", 42);
}
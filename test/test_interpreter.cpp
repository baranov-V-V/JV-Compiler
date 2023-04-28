#include "gtest/gtest.h"

#include "fmt/core.h"
#include "fmt/printf.h"

#include <unordered_map>
#include <string>
#include <deque>

/*
class InterpreterTestVisitor : public Interpreter {
 public:
  InterpreterTestVisitor() = default;
  virtual ~InterpreterTestVisitor() override = default;
  virtual void Visit(PrintStatement* statement) override {
    
  };

 private:
  std::deque<int> expect_values;
};
*/

//WIP

TEST(Hello_world, simple) {
  fmt::print("Hello world {}", 42);
}

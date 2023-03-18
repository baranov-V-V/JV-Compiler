#include <iostream>
#include <string>
#include <fstream>
#include "compiler/parser/driver.hpp"
#include "compiler/core/compiler.hpp"
#include <filesystem>

#include "compiler/core/logger.hpp"

#include "fmt/os.h"


int main(int argc, char** argv) {
  
  Compiler compiler;
  compiler.Compile(argc, argv);

  return 0;
}
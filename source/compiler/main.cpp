#include "compiler/core/logger.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


#include "compiler/parser/driver.hpp"
#include "compiler/core/compiler.hpp"

int main(int argc, char** argv) {
  SetLogLevel(LOG_LEVEL::INFO);
  
  Compiler compiler;
  compiler.Compile(argc, argv);

  return 0;
}
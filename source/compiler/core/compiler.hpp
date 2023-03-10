#pragma once

#include <filesystem>
#include <vector>

#include "compiler/util/compiler_flags.hpp"

class Compiler {
 public:
  Compiler() = default;
  
  void Compile(int argc, char** argv);

 private:
  Driver driver;

  void ParseArgs(int argc, char** argv);

  std::vector<CompilerFlag> flags;
};
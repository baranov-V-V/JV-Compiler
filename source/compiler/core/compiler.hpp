#pragma once

#include <filesystem>
#include <vector>

#include "compiler/util/compiler_flags.hpp"
#include "compiler/parser/driver.hpp"

class Compiler {
 public:
  Compiler() = default;
  
  void Compile(int argc, char** argv);
  
  const Driver& GetDriver() const;

 private:
  std::filesystem::path file_out;
  std::filesystem::path file_in;
  std::filesystem::path dump_txt;
  std::filesystem::path dump_png;

  Driver driver;
  CompilerFlags compiler_flags;

  void ParseArgs(int argc, char** argv);
};
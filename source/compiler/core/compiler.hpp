#pragma once

#include <filesystem>
#include <vector>

#include "core/logger.hpp"

#include "util/compiler_flags.hpp"
#include "parser/driver.hpp"

class Compiler {
 public:
  Compiler() = default;
  ~Compiler() = default;

  void Compile(int argc, char** argv);

  Driver& GetDriver();
  const Driver& GetDriver() const;

  static const char* GetVersion();

 private:
  std::filesystem::path file_out;
  std::filesystem::path file_in;

  Driver driver;

  void ParseArgs(int argc, char** argv);
};
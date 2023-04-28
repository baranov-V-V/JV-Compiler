#pragma once

#include <filesystem>
#include <vector>

#include "compiler/core/logger.hpp"
#include "compiler/util/compiler_flags.hpp"
#include "compiler/parser/driver.hpp"

class Compiler {
 public:
  Compiler() = default;
  
  void Compile(int argc, char** argv);
  
        Driver& GetDriver();
  const Driver& GetDriver() const;

  void SetFileOut(const std::filesystem::path& file_out);
  void SetFileIn(const std::filesystem::path& file_in);
  void SetDumpTxt(const std::filesystem::path& dump_txt);
  void SetDumpPng(const std::filesystem::path& dump_png);

  void SetDebugLevel(LOG_LEVEL level) const;

  void NeedEmitLLVM(bool need_emit);

  static const char* GetVersion();

 private:
  std::filesystem::path file_out;
  std::filesystem::path file_in;
  std::filesystem::path dump_txt;
  std::filesystem::path dump_png;

  bool need_emit;

  Driver driver;
  CompilerFlags compiler_flags;

  void ParseArgs(int argc, char** argv);
};
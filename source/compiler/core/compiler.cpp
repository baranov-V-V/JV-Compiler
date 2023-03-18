#include <string>

#include "compiler/core/logger.hpp"

#include "compiler.hpp"
#include "compiler/parser/driver.hpp"
#include "llvm/Support/CommandLine.h"

void Compiler::Compile(int argc, char** argv) {
  ParseArgs(argc, argv);
  driver.Parse(file_in);

  if (!dump_png.empty()) {
    driver.PrintTreePng(dump_png);
  }
  if (!dump_png.empty()) {
    driver.PrintTreePng(dump_png);
  }

  std::filesystem::path ir_path(file_out);
  std::filesystem::path obj_path(file_out);
  ir_path.replace_extension(".ll");
  obj_path.replace_extension(".o");
  driver.IrGen(ir_path);
  
  /*
  $ llc -filetype=obj hello-world.ll -o hello-world.o
  $ clang hello-world.o -o hello-world
  */
  std::string llc_command = "llc -filetype=obj " + ir_path.native() + " -o " + obj_path.native();
  std::string clang_command = "clang " + obj_path.native() + " -o " + file_out.native();

  LOG_DEBUG("llc compile command {}", llc_command);
  LOG_DEBUG("clang compile command {}", clang_command);

  int llc_errcode = std::system(llc_command.c_str());
  int clang_errcode = std::system(llc_command.c_str());

  LOG_DEBUG("llc errcode {}", llc_errcode);
  LOG_DEBUG("clang errcode  {}", clang_errcode);
}

const Driver& Compiler::GetDriver() const {
  return driver;
}

void Compiler::ParseArgs(int argc, char** argv) {
  compiler_flags.InitFlags();
  compiler_flags.ReadFromCommandLine(argc, argv);
  compiler_flags.Apply(*this);
}

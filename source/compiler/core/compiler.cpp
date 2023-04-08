#include <string>

#include "compiler/core/logger.hpp"

#include "compiler.hpp"
#include "exceptions/compilation_exception.hpp"

void Compiler::Compile(int argc, char** argv) {
  ParseArgs(argc, argv);

  driver.Parse(file_in);

  if (!dump_txt.empty()) {
    driver.PrintTreeTxt(dump_txt);
  }

  if (!dump_png.empty()) {
    driver.PrintTreePng(dump_png);
  }

  driver.BuildLayerTree();

  if (!table_png.empty()) {
    driver.PrintSymbolTree(table_png);
  }

  /*
  std::filesystem::path tmp_dir = file_in.parent_path().append("tmp");
  if (!std::filesystem::exists(tmp_dir)) {
    if (!std::filesystem::create_directory(tmp_dir)) {
      LOG_CRITICAL("could not create tmp directory: {}", tmp_dir.native());
    }
  }

  std::filesystem::path comp_path(file_in.parent_path());
  std::filesystem::path ir_path(tmp_dir);
  std::filesystem::path obj_path(tmp_dir);
  ir_path /= file_in.stem().replace_extension(".ll");
  obj_path /= file_in.stem().replace_extension(".o");

  driver.IrGen(ir_path);

  std::string llc_command = "llc -filetype=obj " + ir_path.native() + " -o " + obj_path.native();
  std::string clang_command = "clang++ " + obj_path.native() + " -o " + file_out.native();

  LOG_DEBUG("llc compile command \"{}\"", llc_command);
  LOG_DEBUG("clang compile command \"{}\"", clang_command);

  int llc_errcode = std::system(llc_command.c_str());
  int clang_errcode = std::system(clang_command.c_str());

  LOG_DEBUG("llc errcode: {}", llc_errcode);
  LOG_DEBUG("clang errcode:  {}", clang_errcode);

  if (need_emit) {

    //std::filesystem::rename(ir_path, file_out.parent_path());
    std::string mv_command = "mv " + ir_path.native() + " .";
    LOG_DEBUG("mv command: {}", mv_command);
    std::system(mv_command.c_str());
  }

  std::filesystem::remove_all(tmp_dir);
  */
}

Driver& Compiler::GetDriver() {
  return driver;
}

const Driver& Compiler::GetDriver() const { return driver; }

void Compiler::SetFileOut(const std::filesystem::path& file_out) {
  this->file_out = file_out;
}

void Compiler::SetFileIn(const std::filesystem::path& file_in) {
  this->file_in = file_in;
}

void Compiler::SetDumpTxt(const std::filesystem::path& dump_txt) {
  this->dump_txt = dump_txt;
}

void Compiler::SetDumpPng(const std::filesystem::path& dump_png) {
  this->dump_png = dump_png;
}

void Compiler::ParseArgs(int argc, char** argv) {
  if (argc < 2) {
    COMPILER_ERROR("no input files\ncompilation terminated.\n")
  }

  compiler_flags.InitFlags();
  compiler_flags.PreprocessFlags();
  compiler_flags.ReadFromCommandLine(argc, argv);
  compiler_flags.Apply(this);
}

void Compiler::SetDebugLevel(LOG_LEVEL level) const {
  SET_LOG_LEVEL(level)
}

void Compiler::NeedEmitLLVM(bool need_emit) {
  this->need_emit = need_emit;
}

const char* Compiler::GetVersion() {
  return "jvc (JV-Complier) version 1.0-SNAPSHOT (x86_64)" ;
}

void Compiler::SetDumpTable(const std::filesystem::path &dump_png) {
  this->table_png = dump_png;
}

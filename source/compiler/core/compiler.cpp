#include <string>

#include "core/logger.hpp"
#include "core/error.hpp"

#include "compiler.hpp"
#include "exceptions/compilation_exception.hpp"

void Compiler::Compile(int argc, const char* argv[]) {
  ParseArgs(argc, argv);

  driver.Parse(file_in);

  if (Flags::Instance().GetFlag<AstDumpTxtFlag>()->IsSet()) {
    driver.PrintTreeTxt(Flags::Instance().GetFlag<AstDumpTxtFlag>()->GetPath());
  }

  if (Flags::Instance().GetFlag<AstDumpPngFlag>()->IsSet()) {
    driver.PrintTreePng(Flags::Instance().GetFlag<AstDumpPngFlag>()->GetPath());
  }

  driver.BuildLayerTree();

  if (Flags::Instance().GetFlag<SymbolTableDumpFlag>()->IsSet()) {
    driver.PrintSymbolTree(Flags::Instance().GetFlag<SymbolTableDumpFlag>()->GetPath());
  }

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

  if (Flags::Instance().GetFlag<CompilerEmitLLVM>()->IsSet()) {
    //std::filesystem::rename(ir_path, file_out.parent_path());
    std::string mv_command = "mv " + ir_path.native() + " .";
    LOG_DEBUG("mv command: {}", mv_command);
    std::system(mv_command.c_str());
  }

  std::filesystem::remove_all(tmp_dir);
}

Driver& Compiler::GetDriver() {
  return driver;
}

const Driver& Compiler::GetDriver() const { return driver; }

void Compiler::ParseArgs(int argc, const char* argv[]) {
  if (argc < 2) {
    COMPILER_ERROR("no input files\ncompilation terminated.\n")
  }

  Flags::Instance().InitFlags();
  Flags::Instance().PreprocessFlags();
  Flags::Instance().ReadFromCommandLine(argc, argv);

  file_in = Flags::Instance().GetFlag<CompileInputFlag>()->GetPath();
  file_out = Flags::Instance().GetFlag<CompileOutputFlag>()->GetPath();
  SET_LOG_LEVEL(Flags::Instance().GetFlag<CompilerDebugLevelFlag>()->GetLevel())
}

const char* Compiler::GetVersion() {
  return "jvc (JV-Complier) version 1.0-SNAPSHOT (x86_64)";
}

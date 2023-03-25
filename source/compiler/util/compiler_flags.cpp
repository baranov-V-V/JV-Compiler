#include "compiler_flags.hpp"
#include "compiler/core/compiler.hpp"

#include <iostream>

TraseParseFlag::TraseParseFlag() :
  trace("p", llvm::cl::desc("Enable tracing of parser part"), llvm::cl::init(false)) {}

void TraseParseFlag::Apply(Compiler* compiler) const {
  compiler->GetDriver().SetTraceParse(trace);
}

TraseScanFlag::TraseScanFlag() :
  trace("s", llvm::cl::desc("Enable tracing of scanner part"), llvm::cl::init(false)) {}

void TraseScanFlag::Apply(Compiler* compiler) const {
  compiler->GetDriver().SetTraceScan(trace);
}

AstDumpTxtFlag::AstDumpTxtFlag() : 
  filename("dmp_txt", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"), llvm::cl::init("")) {}

void AstDumpTxtFlag::Apply(Compiler* compiler) const {
  compiler->SetDumpTxt(filename.getValue());
}

AstDumpPngFlag::AstDumpPngFlag() :
  filename("dmp_png", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"), llvm::cl::init("")) {}

void AstDumpPngFlag::Apply(Compiler* compiler) const {
  compiler->SetDumpPng(filename.getValue());
}

CompileOutputFlag::CompileOutputFlag() :
  output_filename("o", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"), llvm::cl::init("a.out")) {}

void CompileOutputFlag::Apply(Compiler* compiler) const {
  compiler->SetFileOut(output_filename.getValue());
}

CompileInputFlag::CompileInputFlag() : 
  filename(llvm::cl::Positional, llvm::cl::desc("<input file>"), llvm::cl::Required) {}

void CompileInputFlag::Apply(Compiler* compiler) const {
  compiler->SetFileIn(filename.getValue());
}

CompilerFlags::~CompilerFlags() {
  for (CompilerFlag* flag : flags) {
    delete flag;
  }
}

void CompilerFlags::InitFlags() {
  flags.push_back(new CompileInputFlag());
  flags.push_back(new TraseParseFlag());
  flags.push_back(new TraseScanFlag());
  flags.push_back(new AstDumpTxtFlag());
  flags.push_back(new AstDumpPngFlag());
  flags.push_back(new CompileOutputFlag());
  flags.push_back(new CompilerDebugLevelFlag());
}

void CompilerFlags::ReadFromCommandLine(int argc, char** argv) {
  llvm::cl::ParseCommandLineOptions(argc, argv, "This is a small java-like language compiler");
}

void CompilerFlags::Apply(Compiler* compiler) {
  for (const CompilerFlag* flag : flags) {
    flag->Apply(compiler);
  }
}

void CompilerDebugLevelFlag::Apply(Compiler* compiler) const {
  compiler->SetDebugLevel(debug_level.getValue());
}

CompilerDebugLevelFlag::CompilerDebugLevelFlag() :
  debug_level("debug_level", llvm::cl::desc("Choose debug level:"),
              llvm::cl::init(CRITICAL),
              llvm::cl::values(
                  clEnumVal(OFF, "No debug"),
                  clEnumVal(TRACE, "Enable trace level information"),
                  clEnumVal(DEBUG, "Enable debug level information"),
                  clEnumVal(INFO, "Enable info level information"),
                  clEnumVal(WARN, "Enable warn level information"),
                  clEnumVal(ERROR, "Enable error level information"))) {
}

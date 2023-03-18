#include "compiler_flags.hpp"
#include "compiler/core/compiler.hpp"

#include <iostream>

TraseParseFlag::TraseParseFlag() :
  trace("p", llvm::cl::desc("Enable tracing of parser part")) {}

void TraseParseFlag::Apply(const Compiler& compiler) const {}

TraseScanFlag::TraseScanFlag() :
  trace("s", llvm::cl::desc("Enable tracing of scanner part")) {}

void TraseScanFlag::Apply(const Compiler& compiler) const {
  if (trace) {
    std::cout << "trasing!\n";
  }
}

AstDumpTxtFlag::AstDumpTxtFlag() : 
  filename("dmp_txt", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"), llvm::cl::init("")) {}

void AstDumpTxtFlag::Apply(const Compiler& compiler) const {}

AstDumpPngFlag::AstDumpPngFlag() :
  filename("dmp_png", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"), llvm::cl::init("")) {}

void AstDumpPngFlag::Apply(const Compiler& compiler) const {}

CompileOutputFlag::CompileOutputFlag() :
  output_filename("o", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"), llvm::cl::init("a.out")) {}

void CompileOutputFlag::Apply(const Compiler& compiler) const {
  if (output_filename.hasArgStr()) {
    std::cout << output_filename.getValue() << "\n";
  }
}

CompileInputFlag::CompileInputFlag() : 
  filename(llvm::cl::Positional, llvm::cl::desc("<input file>"), llvm::cl::Required) {}

void CompileInputFlag::Apply(const Compiler& compiler) const {
  std::cout << filename.getValue() << "\n";
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
}

void CompilerFlags::ReadFromCommandLine(int argc, char** argv) {
  llvm::cl::ParseCommandLineOptions(argc, argv, "This is a small program compiler");
}

void CompilerFlags::Apply(const Compiler& compiler) {
  for (const CompilerFlag* flag : flags) {
    flag->Apply(compiler);
  }
}

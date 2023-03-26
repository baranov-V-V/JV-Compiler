#include "compiler_flags.hpp"
#include "compiler/core/compiler.hpp"

#include <optional>

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
  filename("dump-txt", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"),
            llvm::cl::init("")) {}

void AstDumpTxtFlag::Apply(Compiler* compiler) const {
  //LOG_DEBUG("ast dump val: {}", filename.getValue())
  compiler->SetDumpTxt(filename.getValue());
}

AstDumpPngFlag::AstDumpPngFlag() :
  filename("dump-pic", llvm::cl::desc("Specify dump output filename"), llvm::cl::value_desc("filename"),
           llvm::cl::init("")) {}

void AstDumpPngFlag::Apply(Compiler* compiler) const {
  if (!filename.getValue().empty()) {
    COMPILER_ERROR("this flag is not yet supported")
  }
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
  flags.push_back(new CompilerDebugLevelFlag());
  flags.push_back(new CompileInputFlag());
  flags.push_back(new TraseParseFlag());
  flags.push_back(new TraseScanFlag());
  flags.push_back(new AstDumpTxtFlag());
  flags.push_back(new AstDumpPngFlag());
  flags.push_back(new CompileOutputFlag());
  flags.push_back(new CompilerEmitLLVM());
}

void CompilerFlags::ReadFromCommandLine(int argc, char** argv) {
  llvm::cl::ParseCommandLineOptions(argc, argv, "This is a small java-like language compiler");
}

void CompilerFlags::Apply(Compiler* compiler) {
  for (const CompilerFlag* flag : flags) {
    flag->Apply(compiler);
  }
}

void CompilerFlags::PreprocessFlags() {
  llvm::StringMap<llvm::cl::Option*> &Map = llvm::cl::getRegisteredOptions();

  llvm::cl::SetVersionPrinter([](llvm::raw_ostream& ostream)->void { ostream << Compiler::GetVersion() << "\n\n"; });

  Map["color"]->setHiddenFlag(llvm::cl::OptionHidden::Hidden);
  Map["help"]->setDescription("Display available options");
  Map["help-list"]->setDescription("Display list of available options");
  Map["dump-pic"]->setHiddenFlag(llvm::cl::OptionHidden::Hidden);
}

void CompilerDebugLevelFlag::Apply(Compiler* compiler) const {
  compiler->SetDebugLevel(debug_level.getValue());
}

CompilerDebugLevelFlag::CompilerDebugLevelFlag() :
  debug_level("debug-level", llvm::cl::desc("Choose debug level:"),
              llvm::cl::init(CRITICAL),
              llvm::cl::values(
                  clEnumVal(OFF, "No debug"),
                  clEnumVal(TRACE, "Enable trace level information"),
                  clEnumVal(DEBUG, "Enable debug level information"),
                  clEnumVal(INFO, "Enable info level information"),
                  clEnumVal(WARN, "Enable warn level information"),
                  clEnumVal(ERROR, "Enable error level information"),
                  clEnumVal(CRITICAL, "Enable critical level information"))) {
}

void CompilerEmitLLVM::Apply(Compiler* compiler) const {
  compiler->NeedEmitLLVM(emit);
}

CompilerEmitLLVM::CompilerEmitLLVM() : emit("emit-llvm", llvm::cl::desc("Show llvm ir representation"),
                                            llvm::cl::init(false)) {}

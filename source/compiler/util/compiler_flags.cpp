#include "compiler_flags.hpp"

#include "core/compiler.hpp"

#include <optional>

TraceParseFlag::TraceParseFlag() :
  BoolFlag(llvm::StringRef(TraceParseFlag::GetName()), llvm::cl::desc("Enable tracing of parser part"), llvm::cl::init(false)) {}

const char* TraceParseFlag::GetName() {
  return "p";
}

TraceScanFlag::TraceScanFlag() :
  BoolFlag(llvm::StringRef(TraceScanFlag::GetName()), llvm::cl::desc("Enable tracing of scanner part"), llvm::cl::init(false)) {}

const char* TraceScanFlag::GetName() {
  return "s";
}

AstDumpTxtFlag::AstDumpTxtFlag() :
  PathFlag(llvm::StringRef(AstDumpTxtFlag::GetName()), llvm::cl::desc("AST text dump"), llvm::cl::value_desc("filename"),
    llvm::cl::init("")) {}

const char* AstDumpTxtFlag::GetName() {
  return "dump-ast-txt";
}

AstDumpPngFlag::AstDumpPngFlag() :
  PathFlag(llvm::StringRef(AstDumpPngFlag::GetName()), llvm::cl::desc("AST graphviz dump"), llvm::cl::value_desc("filename"),
    llvm::cl::init("")) {}

const char* AstDumpPngFlag::GetName() {
  return "dump-ast";
}

CompileOutputFlag::CompileOutputFlag() :
  PathFlag(
    llvm::StringRef(CompileOutputFlag::GetName()),
    llvm::cl::desc("Specify dump output filename"),
    llvm::cl::value_desc("filename"),
    llvm::cl::init("a.out")) {}

const char* CompileOutputFlag::GetName() {
  return "o";
}

CompileInputFlag::CompileInputFlag() :
  PathFlag(llvm::cl::Positional, llvm::cl::desc("<input file>"), llvm::cl::Required) {}

const char* CompileInputFlag::GetName() {
  return "in";
}

/*
void CompilerDebugLevelFlag::Apply(Compiler* compiler) const {
  compiler->SetDebugLevel(debug_level.getValue());
}
*/

CompilerDebugLevelFlag::CompilerDebugLevelFlag() :
  debug_level(
    llvm::StringRef(CompilerDebugLevelFlag::GetName()), llvm::cl::desc("Choose debug level:"),
    llvm::cl::init(CRITICAL),
    llvm::cl::values(
      clEnumVal(OFF, "No debug"),
      clEnumVal(TRACE, "Enable trace level information"),
      clEnumVal(DEBUG, "Enable debug level information"),
      clEnumVal(INFO, "Enable info level information"),
      clEnumVal(WARN, "Enable warn level information"),
      clEnumVal(ERROR, "Enable error level information"),
      clEnumVal(CRITICAL, "Enable critical level information")
    )) {
}

bool CompilerDebugLevelFlag::IsSet() const {
  return true;
}

const char* CompilerDebugLevelFlag::GetName() {
  return "debug-level";
}

LOG_LEVEL CompilerDebugLevelFlag::GetLevel() const {
  return debug_level.getValue();
}

CompilerEmitLLVM::CompilerEmitLLVM() : BoolFlag(
  llvm::StringRef(CompilerEmitLLVM::GetName()), llvm::cl::desc("Show llvm ir representation"),
  llvm::cl::init(false)) {}

const char* CompilerEmitLLVM::GetName() {
  return "emit-llvm";
}

SymbolTableDumpFlag::SymbolTableDumpFlag() :
  PathFlag(
    llvm::StringRef(SymbolTableDumpFlag::GetName()), llvm::cl::desc("Specify symbol table output filename"), llvm::cl::value_desc("filename"),
    llvm::cl::init("")) {}

const char* SymbolTableDumpFlag::GetName() {
  return "dump-table";
}

void Flags::InitFlags() {
  flags.emplace(CompilerDebugLevelFlag::GetName(), new CompilerDebugLevelFlag());
  flags.emplace(CompileInputFlag::GetName(), new CompileInputFlag());
  flags.emplace(SymbolTableDumpFlag::GetName(), new SymbolTableDumpFlag());
  flags.emplace(TraceParseFlag::GetName(), new TraceParseFlag());
  flags.emplace(TraceScanFlag::GetName(), new TraceScanFlag());
  flags.emplace(AstDumpTxtFlag::GetName(), new AstDumpTxtFlag());
  flags.emplace(AstDumpPngFlag::GetName(), new AstDumpPngFlag());
  flags.emplace(CompileOutputFlag::GetName(), new CompileOutputFlag());
  flags.emplace(CompilerEmitLLVM::GetName(), new CompilerEmitLLVM());
}

void Flags::PreprocessFlags() {
  llvm::StringMap<llvm::cl::Option*>& Map = llvm::cl::getRegisteredOptions();

  llvm::cl::SetVersionPrinter([](llvm::raw_ostream& ostream) -> void { ostream << Compiler::GetVersion() << "\n\n"; });

  Map["color"]->setHiddenFlag(llvm::cl::OptionHidden::Hidden);
  Map["help"]->setDescription("Display available options");
  Map["help-list"]->setDescription("Display list of available options");
}

void Flags::ReadFromCommandLine(int argc, char** argv) {
  llvm::cl::ParseCommandLineOptions(argc, argv, "This is a small java-like language compiler");
}

Flags::~Flags() {
  std::for_each(flags.begin(), flags.end(), [](const auto& item){ delete item.second; });
}

bool BoolFlag::IsSet() const {
  return opt.getValue();
}

bool PathFlag::IsSet() const {
  return !str_opt.getValue().empty();
}

std::filesystem::path PathFlag::GetPath() const {
  return str_opt.getValue();
}

CompilerOptimizeLevelFlag::CompilerOptimizeLevelFlag() :
  level(llvm::cl::desc("Choose optimization level:"),
        llvm::cl::values(
          clEnumVal(O0 , "No optimizations"),
          clEnumVal(O1, "Enable trivial optimizations"),
          clEnumVal(O2, "Enable default optimizations"),
          clEnumVal(O3, "Enable expensive optimizations"))) {
}

bool CompilerOptimizeLevelFlag::IsSet() const {
  return true;
}

const char* CompilerOptimizeLevelFlag::GetName() {
  return "optimize";
}

OPTIMIZATION_LEVEL CompilerOptimizeLevelFlag::GetLevel() const {
  return level.getValue();
}

#include <string>

#include "compiler.hpp"
#include "llvm/Support/CommandLine.h"

void Compiler::Compile(int argc, char** argv) {
  ParseArgs(argc, argv);
}

void Compiler::ParseArgs(int argc, char**argv) {
  llvm::cl::OptionCategory TestOptionCat ("Test Options", "These options are to be used when running tests");

  enum OptLevel {
    g, O1, O2, O3
  };

  llvm::cl::opt<OptLevel> OptimizationLevel(llvm::cl::desc("Choose optimization level:"),
    llvm::cl::values(
      clEnumVal(g , "No optimizations, enable debugging"),
      clEnumVal(O1, "Enable trivial optimizations"),
      clEnumVal(O2, "Enable default optimizations"),
      clEnumVal(O3, "Enable expensive optimizations")),
    llvm::cl::cat(TestOptionCat)
    );

  llvm::cl::opt<std::string> OutputFilename("o", llvm::cl::desc("Specify output filename"), llvm::cl::value_desc("filename"));
  
  llvm::cl::opt<std::string> variable("v", llvm::cl::desc("I don't do anything"),
    llvm::cl::value_desc("a string"),
    llvm::cl::init("default-string")
    );

  llvm::cl::extrahelp("\nThis is more help!\n");
  llvm::cl::extrahelp("And even more!\n");

  //Modify options we don't have direct access to
  llvm::StringMap<llvm::cl::Option*> &hack = llvm::cl::getRegisteredOptions();

  //Unhide really useful option and put it in a different category
  assert(hack.count("color") > 0);
  hack["color"]->setHiddenFlag(llvm::cl::Hidden);
  //hack["color"]->setCategory(TestOptionCat);

  llvm::cl::ParseCommandLineOptions(argc, argv, "This is a small program compiler");
}

#pragma once

#include <filesystem>

#include "compiler/core/logger.hpp"
#include "llvm/Support/CommandLine.h"

class CompilerFlag;
class Compiler;

class CompilerFlags {
 public:
  CompilerFlags() = default;
  ~CompilerFlags();

  void InitFlags();
  void ReadFromCommandLine(int argc, char** argv);
  void Apply(Compiler* compiler);

 private:
  std::vector<CompilerFlag*> flags;
};

class CompilerFlag {
 public:
  CompilerFlag() = default;
  virtual ~CompilerFlag() = default;

  CompilerFlag(const CompilerFlag&) = delete;

  virtual void Apply(Compiler* compiler) const = 0;
};

class TraseParseFlag : public CompilerFlag {
 public:
  TraseParseFlag();
  ~TraseParseFlag() override = default;

  void Apply(Compiler* compiler) const override;

 private:
  llvm::cl::opt<bool> trace;
};

class TraseScanFlag : public CompilerFlag {
 public:
  TraseScanFlag();
  ~TraseScanFlag() override = default;

  void Apply(Compiler* compiler) const override;

 private:
  llvm::cl::opt<bool> trace;
};

class AstDumpTxtFlag : public CompilerFlag {
 public:
  AstDumpTxtFlag();
  ~AstDumpTxtFlag() override = default;

  void Apply(Compiler* compiler) const override;
 
 private:
  llvm::cl::opt<std::string> filename;  
};

class AstDumpPngFlag : public CompilerFlag {
 public:
  AstDumpPngFlag();
  ~AstDumpPngFlag() override = default;

  void Apply(Compiler* compiler) const override;
 
 private:
  llvm::cl::opt<std::string> filename;
};

class CompileOutputFlag : public CompilerFlag {
 public:
  CompileOutputFlag();
  ~CompileOutputFlag() override = default;

  void Apply(Compiler* compiler) const override;
 
 private:
  llvm::cl::opt<std::string> output_filename;
};

class CompileInputFlag : public CompilerFlag {
 public:
  CompileInputFlag();
  ~CompileInputFlag() override = default;

  void Apply(Compiler* compiler) const override;
 
 private:
  llvm::cl::opt<std::string> filename;
};

class CompilerDebugLevelFlag : public CompilerFlag {
 public:
  CompilerDebugLevelFlag();
  ~CompilerDebugLevelFlag() override = default;

  void Apply(Compiler* compiler) const override;

 private:
  llvm::cl::opt<LOG_LEVEL> debug_level;
};
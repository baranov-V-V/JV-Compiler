#pragma once

#include <filesystem>

#include "compiler/parser/driver.hpp"
#include "llvm/Support/CommandLine.h"

class CompilerFlag;

class CompilerFlags {
 public:
  CompilerFlags() = default;
  ~CompilerFlags();

  void InitFlags();
  void ReadFromCommandLine(int argc, char** argv);
  void Apply(const Driver& driver);

 private:
  std::vector<CompilerFlag*> flags;
};

class CompilerFlag {
 public:
  CompilerFlag() = default;
  virtual ~CompilerFlag() = default;

  CompilerFlag(const CompilerFlag&) = delete;

  virtual void Apply(const Driver& driver) const = 0;
};

class TraseParseFlag : public CompilerFlag {
 public:
  TraseParseFlag();
  virtual ~TraseParseFlag() = default;

  //TraseParseFlag(const TraseParseFlag&) = delete;

  virtual void Apply(const Driver& driver) const override;

 private:
  llvm::cl::opt<bool> trace;
};

class TraseScanFlag : public CompilerFlag {
 public:
  TraseScanFlag();
  virtual ~TraseScanFlag() = default;

  virtual void Apply(const Driver& driver) const override;

 private:
  llvm::cl::opt<bool> trace;
};

class AstDumpTxtFlag : public CompilerFlag {
 public:
  AstDumpTxtFlag();
  virtual ~AstDumpTxtFlag() = default;

  virtual void Apply(const Driver& driver) const override;
 
 private:
  llvm::cl::opt<std::string> filename;  
};

class AstDumpPngFlag : public CompilerFlag {
 public:
  AstDumpPngFlag();
  virtual ~AstDumpPngFlag() = default;

  virtual void Apply(const Driver& driver) const override;
 
 private:
  llvm::cl::opt<std::string> filename;
};

class CompileOutputFlag : public CompilerFlag {
 public:
  CompileOutputFlag();
  virtual ~CompileOutputFlag() = default;

  virtual void Apply(const Driver& driver) const override;
 
 private:
  llvm::cl::opt<std::string> output_filename;
};

class CompileInputFlag : public CompilerFlag {
 public:
  CompileInputFlag();
  virtual ~CompileInputFlag() = default;

  virtual void Apply(const Driver& driver) const override;
 
 private:
  llvm::cl::opt<std::string> filename;
};
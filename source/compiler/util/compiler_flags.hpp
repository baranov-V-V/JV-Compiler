#pragma once

#include <filesystem>
#include <map>

#include "core/logger.hpp"
#include "llvm/Support/CommandLine.h"
#include "ir/optimization/levels.hpp"

class CompilerFlag;

class Flags {
 public:
  static Flags& Instance() {
    static Flags instance;
    return instance;
  }

 private:
  Flags() = default;

 public:
  ~Flags();
  Flags(Flags const&) = delete;
  void operator=(Flags const&)  = delete;

 public:
  void InitFlags();

  void PreprocessFlags();

  void ReadFromCommandLine(int argc, const char* argv[]);

  template <typename FlagTy>
  FlagTy* GetFlag() {
    return reinterpret_cast<FlagTy*>(flags.at(FlagTy::GetName()));
  }

 private:
  std::unordered_map<std::string, CompilerFlag*> flags;
};

class CompilerFlag {
 public:
  CompilerFlag() = default;

  virtual ~CompilerFlag() = default;

  [[nodiscard]] virtual bool IsSet() const = 0;

  CompilerFlag(const CompilerFlag&) = delete;
};

class BoolFlag : public CompilerFlag {
 public:
  template <class... Values>
  explicit BoolFlag(Values&&... values) : opt(std::forward<Values>(values)...) {};

  ~BoolFlag() override = default;

  [[nodiscard]] bool IsSet() const override;

 private:
  llvm::cl::opt<bool> opt;
};

class PathFlag : public CompilerFlag {
 public:
  template <class... Values>
  explicit PathFlag(Values&&... values) : str_opt(std::forward<Values>(values)...) {};

  ~PathFlag() override = default;

  [[nodiscard]] bool IsSet() const override;

  [[nodiscard]] std::filesystem::path GetPath() const;

 private:
  llvm::cl::opt<std::string> str_opt;
};

class TraceParseFlag : public BoolFlag {
 public:
  TraceParseFlag();

  ~TraceParseFlag() override = default;

  static const char* GetName();
};

class TraceScanFlag : public BoolFlag {
 public:
  TraceScanFlag();

  ~TraceScanFlag() override = default;

  static const char* GetName();
};

class AstDumpTxtFlag : public PathFlag {
 public:
  AstDumpTxtFlag();

  ~AstDumpTxtFlag() override = default;

  static const char* GetName();
};

class AstDumpPngFlag : public PathFlag {
 public:
  AstDumpPngFlag();

  ~AstDumpPngFlag() override = default;

  static const char* GetName();
};

class CompileOutputFlag : public PathFlag {
 public:
  CompileOutputFlag();

  ~CompileOutputFlag() override = default;

  static const char* GetName();
};

class CompileInputFlag : public PathFlag {
 public:
  CompileInputFlag();

  ~CompileInputFlag() override = default;

  static const char* GetName();
};

class CompilerDebugLevelFlag : public CompilerFlag {
 public:
  CompilerDebugLevelFlag();

  ~CompilerDebugLevelFlag() override = default;

  [[nodiscard]] bool IsSet() const override;

  static const char* GetName();

  [[nodiscard]] LOG_LEVEL GetLevel() const;

 private:
  llvm::cl::opt<LOG_LEVEL> debug_level;
};

class CompilerEmitLLVM : public BoolFlag {
 public:
  CompilerEmitLLVM();

  ~CompilerEmitLLVM() override = default;

  static const char* GetName();
};

class SymbolTableDumpFlag : public PathFlag {
 public:
  SymbolTableDumpFlag();

  ~SymbolTableDumpFlag() override = default;

  static const char* GetName();
};

class CompilerOptimizeLevelFlag : public CompilerFlag {
 public:
  CompilerOptimizeLevelFlag();

  ~CompilerOptimizeLevelFlag() override = default;

  [[nodiscard]] bool IsSet() const override;

  static const char* GetName();

  [[nodiscard]] OPTIMIZATION_LEVEL GetLevel() const;

 private:
  llvm::cl::opt<OPTIMIZATION_LEVEL> level;
};
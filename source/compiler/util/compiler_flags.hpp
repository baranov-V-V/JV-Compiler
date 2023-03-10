#pragma once

#include <filesystem>

#include "compiler/parser/driver.hpp"

class CompilerFlag {
 public:
  CompilerFlag() = default;
  virtual ~CompilerFlag() = default;

  virtual void Set(const Driver& driver) const = 0;
};

class ParseTraseFlag : public CompilerFlag {
 public:
  ParseTraseFlag() = default;
  virtual ~ParseTraseFlag() = default;

  virtual void Set(const Driver& driver) const override;
};

class ParseScanFlag : public CompilerFlag {
 public:
  ParseScanFlag() = default;
  virtual ~ParseScanFlag() = default;

  virtual void Set(const Driver& driver) const override;
};

class AstDumpTxtFlag : public CompilerFlag {
 public:
  AstDumpTxtFlag(const std::filesystem::path& path);
  virtual ~AstDumpTxtFlag() = default;

  virtual void Set(const Driver& driver) const override;
 
 private:
  const std::filesystem::path path;
};

class AstDumpPngFlag : public CompilerFlag {
 public:
  AstDumpPngFlag(const std::filesystem::path& path);
  virtual ~AstDumpPngFlag() = default;

  virtual void Set(const Driver& driver) const override;
 
 private:
  const std::filesystem::path path;
};

class CompileOutputFlag : public CompilerFlag {
 public:
  CompileOutputFlag(const std::filesystem::path& path);
  virtual ~CompileOutputFlag() = default;

  virtual void Set(const Driver& driver) const override;
 
 private:
  const std::filesystem::path path;
};

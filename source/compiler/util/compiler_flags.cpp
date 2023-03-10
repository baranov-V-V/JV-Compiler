#include "compiler_flags.hpp"

void ParseTraseFlag::Set(const Driver& driver) const {}

void ParseScanFlag::Set(const Driver& driver) const {}

AstDumpTxtFlag::AstDumpTxtFlag(const std::filesystem::path& path) {}

void AstDumpTxtFlag::Set(const Driver& driver) const {}

AstDumpPngFlag::AstDumpPngFlag(const std::filesystem::path& path) {}

void AstDumpPngFlag::Set(const Driver& driver) const {}

CompileOutputFlag::CompileOutputFlag(const std::filesystem::path& path) {}

void CompileOutputFlag::Set(const Driver& driver) const {}

#pragma once

#include "spdlog/spdlog.h"
#include "fmt/core.h"
#include "fmt/color.h"
#include "exceptions/compilation_exception.hpp"

#define COMPILER_ERROR(...) \
fmt::print("[{}:{}] jvc: ", __FILE__, __LINE__);          \
fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::orange_red), "error: "); \
fmt::print(__VA_ARGS__);    \
fmt::print("\n\n");    \
throw CompilationException();

#define COMPILER_ERROR_POSITIONAL(pos, ...) \
fmt::print("jvc:{}:{} ", pos.begin.line, pos.begin.column);          \
fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::orange_red), "error: "); \
fmt::print(__VA_ARGS__);                    \
fmt::print("\n\n");    \
throw CompilationException();

#define COMPILER_WARNING(...) \
fmt::print("jvc: ");          \
fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::medium_purple), "warning: "); \
fmt::print(__VA_ARGS__);                              \
fmt::print("\n\n");

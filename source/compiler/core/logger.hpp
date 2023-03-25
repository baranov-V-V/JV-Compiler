#pragma once

#include "spdlog/spdlog.h"
#include "fmt/core.h"

enum LOG_LEVEL : int {
  OFF = 0,
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  CRITICAL,
  N_LEVELS
};

void SetLogLevel(LOG_LEVEL level);

#define SET_LOG_LEVEL(level)  SetLogLevel(level);

#define LOG_TRACE(...)    spdlog::log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__);
#define LOG_DEBUG(...)    spdlog::log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::debug, __VA_ARGS__);
#define LOG_INFO(...)     spdlog::log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__);
#define LOG_WARN(...)     spdlog::log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__);
#define LOG_ERROR(...)    spdlog::log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::error, __VA_ARGS__);
#define LOG_CRITICAL(...) spdlog::log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__);

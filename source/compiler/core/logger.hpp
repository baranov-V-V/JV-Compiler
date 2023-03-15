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

void SET_LEVEL(LOG_LEVEL level);

#define LOG_TRACE(...)    spdlog::trace(__VA_ARGS__);
#define LOG_DEBUG(...)    spdlog::debug(__VA_ARGS__);
#define LOG_INFO(...)     spdlog::info(__VA_ARGS__);
#define LOG_WARN(...)     spdlog::warn(__VA_ARGS__);
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__);
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__);
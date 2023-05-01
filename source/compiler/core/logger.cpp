#include "logger.hpp"

void SetLogLevel(LOG_LEVEL level) {
  switch (level) {
    case LOG_LEVEL::OFF:
      spdlog::set_level(spdlog::level::off);
      break;

    case LOG_LEVEL::TRACE:
      spdlog::set_level(spdlog::level::trace);
      break;

    case LOG_LEVEL::DEBUG:
      spdlog::set_level(spdlog::level::debug);
      break;

    case LOG_LEVEL::INFO:
      spdlog::set_level(spdlog::level::info);
      break;

    case LOG_LEVEL::WARN:
      spdlog::set_level(spdlog::level::warn);
      break;

    case LOG_LEVEL::ERROR:
      spdlog::set_level(spdlog::level::err);
      break;

    case LOG_LEVEL::CRITICAL:
      spdlog::set_level(spdlog::level::critical);
      break;

    default:
      fmt::print(stderr, "unknown logger level [{}]", (int) level);
      break;
  }
}
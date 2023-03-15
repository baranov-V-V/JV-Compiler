#include "logger.hpp"

void SET_LEVEL(LOG_LEVEL level) {
  switch (level) {
    case OFF:
      spdlog::set_level(spdlog::level::off);
      break;
    
    case TRACE:
      spdlog::set_level(spdlog::level::trace);
      break;

    case DEBUG:
      spdlog::set_level(spdlog::level::debug);
      break;

    case INFO:
      spdlog::set_level(spdlog::level::info);
      break;

    case WARN:
      spdlog::set_level(spdlog::level::warn);
      break;

    case ERROR:
      spdlog::set_level(spdlog::level::err);
      break;

    case CRITICAL:
      spdlog::set_level(spdlog::level::critical);
      break;
    
    default:
      fmt::print(stderr, "unknown logger level [{}]", level);
      break;
  }
}
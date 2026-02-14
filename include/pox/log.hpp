#pragma once
#include <string>
#include <cstdint>

namespace pox::log {

enum class Level : uint8_t { Trace=0, Debug=1, Info=2, Warn=3, Error=4 };

struct Config {
  Level level = Level::Info;
  bool timestamps = true;
  bool to_stderr = true;
  std::string file_path;
};

void set_config(const Config& cfg);
void trace(const char* fmt, ...);
void debug(const char* fmt, ...);
void info (const char* fmt, ...);
void warn (const char* fmt, ...);
void error(const char* fmt, ...);

} // namespace pox::log

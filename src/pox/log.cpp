#include "pox/log.hpp"
#include <cstdarg>
#include <cstdio>
#include <mutex>
#include <chrono>

namespace pox::log {

static Config g_cfg{};
static std::mutex g_mtx;
static FILE* g_file = nullptr;

static const char* level_str(Level l) {
  switch (l) {
    case Level::Trace: return "TRACE";
    case Level::Debug: return "DEBUG";
    case Level::Info:  return "INFO ";
    case Level::Warn:  return "WARN ";
    case Level::Error: return "ERROR";
  }
  return "INFO";
}

void set_config(const Config& cfg) {
  std::lock_guard<std::mutex> lock(g_mtx);
  g_cfg = cfg;

  if (g_file) { std::fclose(g_file); g_file = nullptr; }
  if (!g_cfg.file_path.empty()) g_file = std::fopen(g_cfg.file_path.c_str(), "ab");
}

static void vlog(Level lvl, const char* fmt, va_list ap) {
  if ((int)lvl < (int)g_cfg.level) return;

  char msg[2048];
  std::vsnprintf(msg, sizeof(msg), fmt, ap);

  std::lock_guard<std::mutex> lock(g_mtx);

  char prefix[128] = {0};
  if (g_cfg.timestamps) {
    using namespace std::chrono;
    auto ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
    std::snprintf(prefix, sizeof(prefix), "[%lld][%s] ", (long long)ms, level_str(lvl));
  } else {
    std::snprintf(prefix, sizeof(prefix), "[%s] ", level_str(lvl));
  }

  if (g_cfg.to_stderr) {
    std::fputs(prefix, stderr);
    std::fputs(msg, stderr);
    std::fputc('\n', stderr);
  }

  if (g_file) {
    std::fputs(prefix, g_file);
    std::fputs(msg, g_file);
    std::fputc('\n', g_file);
    std::fflush(g_file);
  }
}

void trace(const char* fmt, ...) { va_list ap; va_start(ap, fmt); vlog(Level::Trace, fmt, ap); va_end(ap); }
void debug(const char* fmt, ...) { va_list ap; va_start(ap, fmt); vlog(Level::Debug, fmt, ap); va_end(ap); }
void info (const char* fmt, ...) { va_list ap; va_start(ap, fmt); vlog(Level::Info , fmt, ap); va_end(ap); }
void warn (const char* fmt, ...) { va_list ap; va_start(ap, fmt); vlog(Level::Warn , fmt, ap); va_end(ap); }
void error(const char* fmt, ...) { va_list ap; va_start(ap, fmt); vlog(Level::Error, fmt, ap); va_end(ap); }

} // namespace pox::log

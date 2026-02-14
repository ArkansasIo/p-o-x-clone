#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace pox {

struct Config {
  uint32_t cpu_hz = 2'000'000;
  uint32_t frame_hz = 60;
  uint32_t sample_rate = 44100;

  uint16_t lcd_w = 160;
  uint16_t lcd_h = 120;

  bool enable_trace = false;
  bool enable_debugger = false;

  std::string save_prefix = "saves/pox";
};

struct Framebuffer {
  std::vector<uint32_t> rgba;
  uint16_t w = 0, h = 0;
};

struct AudioBuffer {
  std::vector<float> samples;
};

class Machine {
public:
  explicit Machine(Config cfg);
  ~Machine();

  bool load_bootrom(const std::string& path);
  bool load_cartridge(const std::string& path);

  void reset();
  void run_frame();

  void set_buttons(uint16_t mask);

  const Framebuffer& framebuffer() const;
  const AudioBuffer& audio() const;

  uint64_t cycles() const;

  // Persist SRAM on demand (frontend should call on exit).
  bool save_sram();

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace pox

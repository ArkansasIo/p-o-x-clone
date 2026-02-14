#pragma once
#include "pox/types.hpp"
#include <vector>
#include <cstddef>

namespace pox {

class Display {
public:
  Display(u16 w, u16 h);

  u8  read_reg(u16 off) const;
  void write_reg(u16 off, u8 v);

  void render_from_vram(const u8* vram, size_t vram_size);

  const std::vector<u32>& framebuffer_rgba() const { return fb_; }
  u16 width() const { return w_; }
  u16 height() const { return h_; }

private:
  u16 w_, h_;
  std::vector<u32> fb_;

  // Minimal LCD palette state (4 grayscale entries)
  u8 palette_[4] = {0, 85, 170, 255};
};

} // namespace pox

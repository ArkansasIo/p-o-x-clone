#include "pox/hw/display.hpp"
#include <algorithm>

namespace pox {

Display::Display(u16 w, u16 h)
: w_(w), h_(h), fb_(size_t(w) * size_t(h), 0xFF000000u) {}

u8 Display::read_reg(u16 off) const {
  if (off < 4) return palette_[off];
  return 0x00;
}

void Display::write_reg(u16 off, u8 v) {
  if (off < 4) palette_[off] = v;
}

void Display::render_from_vram(const u8* vram, size_t vram_size) {
  // Placeholder 2bpp packed pixels, 4 pixels per byte:
  // bits [7:6][5:4][3:2][1:0]
  const size_t px = size_t(w_) * size_t(h_);
  const size_t needed = (px + 3) / 4;
  const size_t n = std::min(needed, vram_size);

  size_t p = 0;
  for (size_t i = 0; i < n && p < px; i++) {
    const u8 b = vram[i];
    for (int k = 0; k < 4 && p < px; k++) {
      const int shift = 6 - 2 * k;
      const u8 idx = (b >> shift) & 0x3;
      const u8 g = palette_[idx];
      fb_[p++] = 0xFF000000u | (u32(g) << 16) | (u32(g) << 8) | u32(g);
    }
  }
  // If VRAM shorter than framebuffer, remaining pixels keep previous values.
}

} // namespace pox

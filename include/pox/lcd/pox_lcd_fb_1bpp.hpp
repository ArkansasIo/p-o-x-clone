#pragma once
#include <cstdint>
#include <vector>

namespace pox {
namespace lcd {

// LCD framebuffer (128x64, 1bpp)
struct Framebuffer1bpp {
    static constexpr int WIDTH = 128;
    static constexpr int HEIGHT = 64;
    std::vector<uint8_t> pixels; // Packed 1bpp, row-major

    Framebuffer1bpp();
    void clear();
    void draw_sprite(const Sprite1bpp& sprite, int x, int y);
};

} // namespace lcd
} // namespace pox

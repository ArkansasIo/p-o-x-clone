#include "pox_lcd_fb_1bpp.hpp"

namespace pox {
namespace lcd {

Framebuffer1bpp::Framebuffer1bpp() {
    pixels.resize(WIDTH * HEIGHT / 8, 0);
}

void Framebuffer1bpp::clear() {
    std::fill(pixels.begin(), pixels.end(), 0);
}

void Framebuffer1bpp::draw_sprite(const Sprite1bpp& sprite, int x, int y) {
    // TODO: Implement 1bpp sprite drawing
}

} // namespace lcd
} // namespace pox

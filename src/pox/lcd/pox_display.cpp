#include "pox_display.hpp"

namespace pox {
namespace lcd {

Display::Display(Mode mode) : mode_(mode) {}

void Display::clear() {
    fb_.clear();
    // TODO: Clear segment icons
}

void Display::draw_sprite(const Sprite1bpp& sprite, int x, int y) {
    fb_.draw_sprite(sprite, x, y);
}

void Display::draw_icon(const UIIcon& icon, int x, int y) {
    // TODO: Draw UI icon
}

void Display::set_segment_icon(const SegmentIcon& icon, int idx) {
    // TODO: Set segment icon at index
}

void Display::present() {
    // TODO: Push framebuffer/segments to hardware
}

} // namespace lcd
} // namespace pox

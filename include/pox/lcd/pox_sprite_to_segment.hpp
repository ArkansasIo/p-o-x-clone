#pragma once
#include <cstdint>
#include <vector>
#include "pox_lcd_segment_icons.hpp"
#include "pox_lcd_sprites_1bpp.hpp"

namespace pox {
namespace lcd {

// Map pixel sprite to segment icon
SegmentIcon sprite_to_segment(const Sprite1bpp& sprite);

} // namespace lcd
} // namespace pox

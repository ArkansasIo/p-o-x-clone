#pragma once
#include <cstdint>
#include <vector>

namespace pox {
namespace lcd {

// UI icon definition (for pixel LCD)
struct UIIcon {
    uint8_t width;
    uint8_t height;
    std::vector<uint8_t> data; // Packed 1bpp
};

// Icon pack
struct UIIconPack {
    std::vector<UIIcon> icons;
};

} // namespace lcd
} // namespace pox

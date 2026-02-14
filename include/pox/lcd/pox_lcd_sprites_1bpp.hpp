#pragma once
#include <cstdint>
#include <vector>

namespace pox {
namespace lcd {

// 1-bit pixel sprite definition (8x8, 16x16)
struct Sprite1bpp {
    uint8_t width;
    uint8_t height;
    std::vector<uint8_t> data; // Packed 1bpp, row-major
};

// Sprite pack (all sprites for LCD)
struct SpritePack1bpp {
    std::vector<Sprite1bpp> sprites;
};

// Example: Load sprite pack from binary asset
SpritePack1bpp load_sprite_pack(const char* path);

} // namespace lcd
} // namespace pox

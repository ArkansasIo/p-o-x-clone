// sprite_decoder.cpp
#include "sprite_decoder.hpp"
#include <vector>
#include <cstdint>

std::vector<uint32_t> decode_sprite(const uint8_t* data, uint16_t width, uint16_t height, uint8_t bpp) {
    std::vector<uint32_t> fb(width * height, 0xFF000000);
    for (uint16_t y = 0; y < height; ++y) {
        for (uint16_t x = 0; x < width; ++x) {
            uint8_t pixel = 0;
            if (bpp == 1) {
                pixel = (data[(y * width + x) / 8] >> (7 - (x % 8))) & 1;
            } else if (bpp == 2) {
                pixel = (data[(y * width + x) / 4] >> (6 - 2 * (x % 4))) & 3;
            }
            uint32_t color = 0xFF000000;
            if (bpp == 1) {
                color |= pixel ? 0xFFFFFFFF : 0xFF000000;
            } else if (bpp == 2) {
                color |= (pixel == 0 ? 0xFF000000 : pixel == 1 ? 0xFFAAAAAA : pixel == 2 ? 0xFF555555 : 0xFF222222);
            }
            fb[y * width + x] = color;
        }
    }
    return fb;
}

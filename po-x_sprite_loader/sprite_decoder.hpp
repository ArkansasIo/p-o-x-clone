// sprite_decoder.hpp
#pragma once
#include <vector>
#include <cstdint>

std::vector<uint32_t> decode_sprite(const uint8_t* data, uint16_t width, uint16_t height, uint8_t bpp);

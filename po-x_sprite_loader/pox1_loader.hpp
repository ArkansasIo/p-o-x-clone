
#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct SpriteIndexEntry {
    std::string id;
    uint32_t offset;
    uint32_t size;
    uint8_t bpp;
    uint16_t width;
    uint16_t height;
    uint8_t frames;
};

std::vector<SpriteIndexEntry> load_pox1_index(const std::string& path);

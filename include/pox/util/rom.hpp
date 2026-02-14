#pragma once
#include "pox/types.hpp"
#include <string>
#include <vector>

namespace pox::util {

struct PoxrContainer {
  u32 version = 1;
  std::vector<u8> payload;
  u32 crc = 0;
};

// Load either:
// - raw ROM (fallback), or
// - POXR container (magic "POXR")
bool load_rom_auto(const std::string& path, std::vector<u8>& out_payload);

// Build POXR container bytes from payload
std::vector<u8> build_poxr(u32 version, const std::vector<u8>& payload);

} // namespace pox::util

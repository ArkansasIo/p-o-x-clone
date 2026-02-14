#pragma once
#include <cstdint>

namespace pox {
using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

enum Button : u16 {
  BTN_UP     = 1 << 0,
  BTN_DOWN   = 1 << 1,
  BTN_LEFT   = 1 << 2,
  BTN_RIGHT  = 1 << 3,
  BTN_A      = 1 << 4,
  BTN_B      = 1 << 5,
  BTN_START  = 1 << 6,
  BTN_SELECT = 1 << 7,
};
} // namespace pox

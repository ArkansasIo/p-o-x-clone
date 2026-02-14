#pragma once
#include "pox/types.hpp"

namespace pox::util {

// Common tiny helpers used in CPU/IO code.
// Keep these header-only for ease of use.

inline u8 lo8(u16 v) { return (u8)(v & 0xFF); }
inline u8 hi8(u16 v) { return (u8)((v >> 8) & 0xFF); }

inline u16 make16(u8 lo, u8 hi) { return (u16(hi) << 8) | u16(lo); }

inline bool test_bit(u8 v, int b) { return (v & (u8(1) << b)) != 0; }
inline void set_bit(u8& v, int b, bool on) {
  if (on) v |= (u8(1) << b);
  else    v &= (u8)~(u8(1) << b);
}

} // namespace pox::util

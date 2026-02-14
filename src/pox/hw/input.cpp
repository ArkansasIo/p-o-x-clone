#include "pox/hw/input.hpp"

namespace pox {

u8 Input::read_reg(u16 off) const {
  if (off == 0x00) return (u8)(buttons_ & 0xFF);
  if (off == 0x01) return (u8)((buttons_ >> 8) & 0xFF);
  return 0;
}

void Input::write_reg(u16, u8) {
  // Typically read-only.
}

} // namespace pox

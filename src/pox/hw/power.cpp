#include "pox/hw/power.hpp"

namespace pox {

u8 Power::read_reg(u16 off) const {
  if (off == 0x00) return sleep_ ? 1 : 0;
  if (off == 0x01) return lcd_off_ ? 1 : 0;
  return 0;
}

void Power::write_reg(u16 off, u8 v) {
  if (off == 0x00) sleep_ = (v & 1) != 0;
  if (off == 0x01) lcd_off_ = (v & 1) != 0;
}

} // namespace pox

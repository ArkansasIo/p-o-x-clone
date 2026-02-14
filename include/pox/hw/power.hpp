#pragma once
#include "pox/types.hpp"

namespace pox {

class Power {
public:
  void reset() { sleep_ = false; lcd_off_ = false; }

  void set_sleep(bool on) { sleep_ = on; }
  bool sleeping() const { return sleep_; }

  void set_lcd_off(bool on) { lcd_off_ = on; }
  bool lcd_off() const { return lcd_off_; }

  u8  read_reg(u16 off) const;
  void write_reg(u16 off, u8 v);

private:
  bool sleep_ = false;
  bool lcd_off_ = false;
};

} // namespace pox

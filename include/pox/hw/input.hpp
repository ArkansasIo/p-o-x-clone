#pragma once
#include "pox/types.hpp"

namespace pox {

class Input {
public:
  void set_buttons(u16 mask) { buttons_ = mask; }

  u8  read_reg(u16 off) const;
  void write_reg(u16 off, u8 v);

private:
  u16 buttons_ = 0;
};

} // namespace pox

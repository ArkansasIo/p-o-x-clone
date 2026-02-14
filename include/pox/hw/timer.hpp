#pragma once
#include "pox/types.hpp"

namespace pox {

class Timer {
public:
  void reset();
  void step(u32 cpu_cycles);

  u8  read_reg(u16 off) const;
  void write_reg(u16 off, u8 v);

  bool poll_timer_irq();

private:
  u16 div_ = 0;
  u8 tima_ = 0;
  u8 tma_  = 0;
  u8 tac_  = 0;

  u32 div_acc_ = 0;
  u32 tima_acc_ = 0;
  bool irq_ = false;

  u32 tima_period_cycles() const;
  bool enabled() const { return (tac_ & 0x04) != 0; }
};

} // namespace pox

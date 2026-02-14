#include "pox/hw/timer.hpp"

namespace pox {

void Timer::reset() {
  div_ = 0;
  tima_ = tma_ = tac_ = 0;
  div_acc_ = tima_acc_ = 0;
  irq_ = false;
}

u32 Timer::tima_period_cycles() const {
  switch (tac_ & 0x03) {
    case 0: return 1024;
    case 1: return 16;
    case 2: return 64;
    case 3: return 256;
  }
  return 1024;
}

void Timer::step(u32 cpu_cycles) {
  div_acc_ += cpu_cycles;
  while (div_acc_ >= 256) {
    div_acc_ -= 256;
    div_++;
  }

  if (!enabled()) return;

  tima_acc_ += cpu_cycles;
  const u32 per = tima_period_cycles();
  while (tima_acc_ >= per) {
    tima_acc_ -= per;
    const u8 prev = tima_;
    tima_++;
    if (prev == 0xFF) {
      tima_ = tma_;
      irq_ = true;
    }
  }
}

bool Timer::poll_timer_irq() {
  const bool r = irq_;
  irq_ = false;
  return r;
}

u8 Timer::read_reg(u16 off) const {
  switch (off) {
    case 0x00: return (u8)(div_ & 0xFF);
    case 0x01: return (u8)((div_ >> 8) & 0xFF);
    case 0x02: return tima_;
    case 0x03: return tma_;
    case 0x04: return tac_;
    default:   return 0x00;
  }
}

void Timer::write_reg(u16 off, u8 v) {
  switch (off) {
    case 0x00:
    case 0x01:
      div_ = 0;
      div_acc_ = 0;
      break;
    case 0x02: tima_ = v; break;
    case 0x03: tma_  = v; break;
    case 0x04: tac_  = (u8)(v & 0x07); break;
    default: break;
  }
}

} // namespace pox

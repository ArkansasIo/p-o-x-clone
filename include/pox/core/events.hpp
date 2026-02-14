#pragma once
#include "pox/types.hpp"

namespace pox {

// Minimal event/interrupt scaffold. Real PO-X will define actual sources.
enum class Event : u8 {
  None = 0,
  TimerIRQ = 1,
  VBlank = 2,
};

struct EventFlags {
  u8 pending = 0;
  void raise(Event e) { pending |= (u8)e; }
  bool test(Event e) const { return (pending & (u8)e) != 0; }
  void clear(Event e) { pending &= (u8)~(u8)e; }
  void clear_all() { pending = 0; }
};

} // namespace pox

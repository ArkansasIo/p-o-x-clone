#pragma once
#include "pox/types.hpp"

namespace pox {

class Bus;

struct CPUState {
  u16 pc = 0x0000;
  u8  a = 0, x = 0, y = 0;
  u8  sp = 0xFF;
  u8  flags = 0;
  u64 cycles = 0;
  bool halted = false;
};

class CPU8 {
public:
  explicit CPU8(Bus& bus);

  void reset(u16 pc);
  u32 step();

  const CPUState& state() const { return s_; }

private:
  Bus& bus_;
  CPUState s_;

  u8  fetch8();
  u16 fetch16();

  // Placeholder ops
  u32 op_nop();
  u32 op_lda_imm();
  u32 op_jmp_abs();
  u32 op_sta_abs();
  u32 op_lda_abs();
  u32 op_add_imm();
  u32 op_brk();
};

} // namespace pox

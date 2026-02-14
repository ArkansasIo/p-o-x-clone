#include "pox/hw/cpu8.hpp"
#include "pox/core/bus.hpp"
#include "pox/util/bitops.hpp"

namespace pox {

CPU8::CPU8(Bus& bus) : bus_(bus) {}

void CPU8::reset(u16 pc) {
  s_ = {};
  s_.pc = pc;
  s_.sp = 0xFF;
  s_.halted = false;
}

u8 CPU8::fetch8() {
  u8 v = bus_.read8(s_.pc);
  s_.pc++;
  return v;
}

u16 CPU8::fetch16() {
  u16 lo = fetch8();
  u16 hi = fetch8();
  return (hi << 8) | lo;
}

u32 CPU8::op_nop() { return 2; }

u32 CPU8::op_lda_imm() {
  s_.a = fetch8();
  return 2;
}

u32 CPU8::op_jmp_abs() {
  s_.pc = fetch16();
  return 3;
}

u32 CPU8::op_sta_abs() {
  const u16 a = fetch16();
  bus_.write8(a, s_.a);
  return 4;
}

u32 CPU8::op_lda_abs() {
  const u16 a = fetch16();
  s_.a = bus_.read8(a);
  return 4;
}

u32 CPU8::op_add_imm() {
  const u8 imm = fetch8();
  s_.a = (u8)(s_.a + imm);
  return 2;
}

u32 CPU8::op_brk() {
  s_.halted = true;
  return 2;
}

u32 CPU8::step() {
  if (s_.halted) { s_.cycles += 1; return 1; }

  const u8 op = fetch8();

  u32 c = 0;
  switch (op) {
    case 0x00: c = op_nop(); break;
    case 0x01: c = op_lda_imm(); break;
    case 0x02: c = op_jmp_abs(); break;
    case 0x10: c = op_sta_abs(); break;
    case 0x11: c = op_lda_abs(); break;
    case 0x20: c = op_add_imm(); break;
    case 0x30: c = op_brk(); break;
    default:
      // Unknown opcode: treat as NOP in scaffold.
      c = 2;
      break;
  }

  s_.cycles += c;
  return c;
}

} // namespace pox

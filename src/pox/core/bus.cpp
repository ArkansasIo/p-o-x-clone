#include "pox/core/bus.hpp"
#include "pox/hw/memory.hpp"
#include "pox/hw/display.hpp"
#include "pox/hw/input.hpp"
#include "pox/hw/timer.hpp"
#include "pox/hw/audio.hpp"
#include "pox/hw/power.hpp"
#include "pox/hw/cartridge.hpp"

namespace pox {

// Placeholder memory map:
// 0x0000-0x3FFF : Cart ROM bank 0
// 0x4000-0x7FFF : Cart ROM banked
// 0x8000-0x87FF : VRAM
// 0x8800-0x8FFF : IO
// 0x9000-0x97FF : RAM
// 0x9800-0x9FFF : Cart SRAM

static constexpr u16 CART0_START = 0x0000;
static constexpr u16 CART0_END   = 0x3FFF;
static constexpr u16 CARTB_START = 0x4000;
static constexpr u16 CARTB_END   = 0x7FFF;

static constexpr u16 VRAM_START  = 0x8000;
static constexpr u16 VRAM_END    = 0x87FF;

static constexpr u16 IO_START    = 0x8800;
static constexpr u16 IO_END      = 0x8FFF;

static constexpr u16 RAM_START   = 0x9000;
static constexpr u16 RAM_END     = 0x97FF;

static constexpr u16 SRAM_START  = 0x9800;
static constexpr u16 SRAM_END    = 0x9FFF;

Bus::Bus(Memory& mem, Display& lcd, Input& in, Timer& tmr, Audio& aud, Power& pwr, Cartridge& cart)
: mem_(mem), lcd_(lcd), in_(in), tmr_(tmr), aud_(aud), pwr_(pwr), cart_(cart) {}

u8 Bus::read8(u16 addr) {
  if (addr >= CART0_START && addr <= CARTB_END) return cart_.read8(addr);
  if (addr >= VRAM_START && addr <= VRAM_END)   return mem_.vram_read(addr - VRAM_START);
  if (addr >= RAM_START  && addr <= RAM_END)    return mem_.ram_read(addr - RAM_START);
  if (addr >= SRAM_START && addr <= SRAM_END)   return cart_.sram_read(addr - SRAM_START);

  if (addr >= IO_START && addr <= IO_END) {
    const u16 o = addr - IO_START;
    if (o < 0x0100) return lcd_.read_reg(o);
    if (o < 0x0200) return in_.read_reg(o - 0x0100);
    if (o < 0x0300) return tmr_.read_reg(o - 0x0200);
    if (o < 0x0400) return aud_.read_reg(o - 0x0300);
    if (o < 0x0500) return pwr_.read_reg(o - 0x0400);
    return 0xFF;
  }

  return 0xFF;
}

void Bus::write8(u16 addr, u8 v) {
  if (addr >= CART0_START && addr <= CARTB_END) { cart_.write8(addr, v); return; }
  if (addr >= VRAM_START && addr <= VRAM_END)   { mem_.vram_write(addr - VRAM_START, v); return; }
  if (addr >= RAM_START  && addr <= RAM_END)    { mem_.ram_write(addr - RAM_START, v); return; }
  if (addr >= SRAM_START && addr <= SRAM_END)   { cart_.sram_write(addr - SRAM_START, v); return; }

  if (addr >= IO_START && addr <= IO_END) {
    const u16 o = addr - IO_START;
    if (o < 0x0100) { lcd_.write_reg(o, v); return; }
    if (o < 0x0200) { in_.write_reg(o - 0x0100, v); return; }
    if (o < 0x0300) { tmr_.write_reg(o - 0x0200, v); return; }
    if (o < 0x0400) { aud_.write_reg(o - 0x0300, v); return; }
    if (o < 0x0500) { pwr_.write_reg(o - 0x0400, v); return; }
    return;
  }
}

u16 Bus::read16(u16 addr) {
  const u16 lo = read8(addr);
  const u16 hi = read8(addr + 1);
  return (hi << 8) | lo;
}

void Bus::write16(u16 addr, u16 v) {
  write8(addr, (u8)(v & 0xFF));
  write8(addr + 1, (u8)((v >> 8) & 0xFF));
}

} // namespace pox

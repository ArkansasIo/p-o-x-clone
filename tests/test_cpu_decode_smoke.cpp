#include "pox/hw/memory.hpp"
#include "pox/hw/display.hpp"
#include "pox/hw/input.hpp"
#include "pox/hw/timer.hpp"
#include "pox/hw/audio.hpp"
#include "pox/hw/power.hpp"
#include "pox/hw/cartridge.hpp"
#include "pox/core/bus.hpp"
#include "pox/hw/cpu8.hpp"
#include <cassert>

int test_cpu_decode_smoke() {
  pox::Memory mem; mem.reset();
  pox::Display lcd(16,16);
  pox::Input in;
  pox::Timer tmr; tmr.reset();
  pox::Audio aud; aud.reset(44100);
  pox::Power pwr; pwr.reset();
  pox::Cartridge cart;

  pox::Bus bus(mem, lcd, in, tmr, aud, pwr, cart);
  pox::CPU8 cpu(bus);
  cpu.reset(0x0000);

  auto c = cpu.step();
  assert(c > 0);
  return 0;
}

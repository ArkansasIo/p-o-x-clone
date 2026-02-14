#pragma once
#include "pox/types.hpp"

namespace pox {

class Memory;
class Display;
class Input;
class Timer;
class Audio;
class Power;
class Cartridge;

class Bus {
public:
  Bus(Memory& mem, Display& lcd, Input& in, Timer& tmr, Audio& aud, Power& pwr, Cartridge& cart);

  u8  read8(u16 addr);
  void write8(u16 addr, u8 v);

  u16 read16(u16 addr);
  void write16(u16 addr, u16 v);

private:
  Memory& mem_;
  Display& lcd_;
  Input& in_;
  Timer& tmr_;
  Audio& aud_;
  Power& pwr_;
  Cartridge& cart_;
};

} // namespace pox

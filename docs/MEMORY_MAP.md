# Memory Map (PLACEHOLDER)

This scaffold uses a GameBoy-like address split so you have a working structure.

## 16-bit address space (0x0000-0xFFFF) — placeholder
- 0x0000-0x3FFF: ROM bank 0
- 0x4000-0x7FFF: ROM banked window (16KB)
- 0x8000-0x87FF: VRAM (2KB placeholder)
- 0x8800-0x8FFF: IO page (LCD/Input/Timer/Audio/Power)
- 0x9000-0x97FF: RAM (2KB placeholder)
- 0x9800-0x9FFF: Cartridge SRAM (8KB placeholder via modulo)

## IO page (offset = addr - 0x8800)
- 0x000-0x0FF: LCD regs
- 0x100-0x1FF: Input regs
- 0x200-0x2FF: Timer regs
- 0x300-0x3FF: Audio regs
- 0x400-0x4FF: Power regs

Replace this once you confirm the real PO-X map.

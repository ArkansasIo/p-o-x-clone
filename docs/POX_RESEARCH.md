# PO-X Handheld Research Summary

## What is PO-X?
PO-X (Pocket Monsters/Pocket-X) refers to a family of early-2000s digital pet/creature handhelds, often inspired by Tamagotchi and Pokémon. These devices featured:
- 8-bit microcontroller (custom or clone, simple ISA)
- LCD display (typically 2bpp, 4-shade grayscale)
- D-pad + A/B/Start/Select buttons
- SRAM for save data (creature records, progress)
- ROM for game logic
- Simple audio (beeper or PWM)

## Typical Hardware Architecture
- CPU: 8-bit, custom or clone (often Z80, 6502, or proprietary)
- RAM: 2–8 KB
- VRAM: 2 KB (for LCD framebuffer)
- ROM: 32–256 KB
- SRAM: 512 B–8 KB (battery-backed)
- IO: memory-mapped registers for LCD, input, timer, audio

## Memory Map (Example)
| Address    | Function         |
|------------|-----------------|
| 0x0000-3FFF| ROM bank 0       |
| 0x4000-7FFF| ROM banked       |
| 0x8000-87FF| VRAM             |
| 0x8800-8FFF| IO registers     |
| 0x9000-97FF| RAM              |
| 0x9800-9FFF| SRAM (save)      |

## Game Features
- Digital pet/creature with stats (HP, mood, hunger, etc)
- Menu UI for actions (Feed, Play, Heal, Save, Load)
- Persistent save slots (SRAM, CRC-protected)
- Simple minigames or stat management
- Input-driven gameplay (D-pad, A/B)

## Reverse Engineering Tips
- Dump ROM and SRAM to analyze code/data
- Look for memory-mapped IO patterns (LCD, input)
- Trace CPU execution to find menu/action logic
- Identify save record format (often fixed-size, CRC)
- Use emulator trace/debug features to validate behavior

## References
- [Handheld Museum](http://www.handheldmuseum.com/)
- [Tamagotchi Reverse Engineering](https://tama.cafe/)
- [Pokémon Mini Documentation](https://problemkaputt.de/pokemini.htm)

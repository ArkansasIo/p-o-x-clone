
# POX Clone Architecture Overview

This document describes the core architecture and design principles of the POX Clone emulator and game engine. It is intended for developers and contributors seeking to understand or extend the system.

# Dev Credit: Stephen Deline Jr
# Architecture (PO-X Clone Scaffold)

## Core principles
- **Deterministic**: no timing drift across frames.
- **Layered**: CPU accesses memory via Bus only.
- **Replaceable**: opcodes + memory map can be swapped without breaking the project.

## Components
- `Clock` — computes cycle budget per frame and provides cycle->audio sample conversion.
- `CPU8` — placeholder 8-bit CPU core with a decode table.
- `Bus` — routes reads/writes to ROM, RAM, VRAM, IO devices.
- `Timer` — divider + programmable timer (placeholder).
- `Audio` — minimal PSG-like square wave generator (placeholder).
- `Display` — converts VRAM into RGBA framebuffer (2bpp packed placeholder).
- `Input` — button register block.
- `Cartridge` — ROM + SRAM + banking + save persistence.

## Frame loop (Machine::run_frame)
1. Get `budget_cycles` from `Clock::begin_frame_budget()`.
2. While cycles < budget:
   - optional debugger stop
   - optional trace snapshot
   - execute one CPU instruction (returns cycles)
   - step timer by cycles
   - step audio by cycles -> produce sample budget
3. Render display from VRAM
4. Drain audio to frontend


## Extending the Architecture
- To add new hardware features, implement or extend the relevant component in `src/pox/hw/` or `src/pox/core/`.
- For new CPU instructions, update `cpu8.cpp` and its decode table.
- For new memory maps or IO, modify `bus.cpp`.
- For display or timing changes, see `display.cpp` and `timer.cpp`.
- For cartridge or save changes, see `cartridge.cpp`.

For more details, see related documents in this folder.

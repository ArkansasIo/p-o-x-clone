# Technical Design Document (TDD) — PO-X Legacy Clone

## 1. Goals
- Provide a clean, testable, emulator-grade architecture.
- Keep hardware blocks isolated and connected through a Bus.
- Ensure deterministic timing independent of wall clock.

## 2. Non-Goals (for scaffold phase)
- Exact accuracy of PO-X hardware without specs/dumps.
- GUI debugger (core APIs only for now).

## 3. Architecture Overview
Core objects:
- Machine: orchestrates one-frame stepping and IO
- Clock: cycle budgets per frame + cycles->audio conversion
- CPU8: placeholder CPU core (replace with real ISA)
- Bus: memory-mapped routing (replace map with real)
- Display: VRAM->RGBA conversion (replace LCD pipeline)
- Timer: divider + programmable timer (replace divisors/IRQ)
- Audio: square-wave stub (replace PSG/PWM)
- Cartridge: ROM/SRAM + bank switching + saves

## 4. Timing Model
- Budget cycles per frame = cpu_hz/frame_hz with remainder compensation.
- CPU step returns cycles consumed per instruction.
- Peripherals step using those cycles.
- Frontend delays to maintain frame pacing (SDL app).

## 5. Save System
- SRAM persisted to `<save_prefix>.sav`
- Future: SaveStates to `.state` snapshots, rewind ring buffer.

## 6. Extensibility Points
### Replace CPU ISA
- `src/pox/hw/cpu8.cpp` and `include/pox/hw/cpu8.hpp`
### Replace Memory Map
- `src/pox/core/bus.cpp`
### Replace LCD Rendering
- `src/pox/hw/display.cpp`
### Replace Audio Hardware
- `src/pox/hw/audio.cpp`
### Add IRQ/Events
- `include/pox/core/events.hpp` plus CPU IRQ wiring

## 7. Testing Strategy
- Unit tests for utilities (CRC32, ROM container)
- Smoke tests for CPU stepping/bus integration
- Add CPU instruction tests once ISA known (golden traces)

## 8. Build
- CMake + optional SDL frontend flag `POX_BUILD_SDL`

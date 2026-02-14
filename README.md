# PO-X (2001) Handheld Clone — Emulator Scaffold (C++20 + SDL2)

This repository is a **hardware-emulation scaffold** for a PO-X–style handheld (circa 2001).
It is intentionally designed to be **emulator-like and extensible**: once you confirm the real
CPU/opcodes, memory map, LCD pipeline, and cartridge behavior, you can plug those details in
without rewriting the architecture.

## What you get (today)

- Deterministic core loop (Clock -> CPU -> Timer/Audio -> LCD render)
- Memory-mapped IO through a Bus router
- Cartridge ROM + SRAM + save persistence (`.sav`)
- Trace buffer (instruction-level trace for debugging/diffing)
- Debugger scaffold (breakpoints + watchpoints)
- ROM container spec ("POXR") + packer tool
- SDL2 desktop runner

> **Important:** CPU opcodes and memory map are placeholders by design.

## Build

### Dependencies
- CMake 3.22+
- C++20 compiler
- SDL2 development package

#### Windows/CMake: Setting up SDL2
1. Download and extract the SDL2 development package (already included in this repo under `SDL2-devel-2.30.2-VC`).
2. Set the `SDL2_DIR` environment variable to the full path of the SDL2 folder. For example:
   - `D:/pox-clone/pox-clone/SDL2-devel-2.30.2-VC/SDL2-2.30.2`
3. Ensure the `include` and `lib` folders are present inside this directory.
4. Re-run CMake to configure the project.

### Configure & compile
```bash
cmake -S . -B build
cmake --build build -j
```

## Run
```bash
./build/apps/desktop_sdl/pox_desktop path/to/game.rom
```

Keyboard mapping (default):
- Arrow keys: D-pad
- Z: A
- X: B
- Enter: Start
- Right Shift: Select
- Esc: Quit

## Tests
```bash
cmake -S . -B build
cmake --build build -j
./build/tests/pox_tests
```

## Where to implement the real PO-X hardware

1) **CPU**: `src/pox/hw/cpu8.cpp`  
2) **Memory map / IO registers**: `src/pox/core/bus.cpp`  
3) **LCD pipeline**: `src/pox/hw/display.cpp`  
4) **Timers / interrupts**: `src/pox/hw/timer.cpp` + CPU IRQ plumbing  
5) **Cartridge banking / save**: `src/pox/hw/cartridge.cpp`

See `/docs` for architecture + placeholder specs.



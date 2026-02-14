# Debugging

## Trace
Enable trace by setting `Config.enable_trace = true`.
The core will push a `TraceEntry` each CPU step with:
- PC, opcode (peek), register snapshot, cycle count

Dump trace text via `TraceBuffer::dump_text()`.

## Debugger scaffold
`Debugger` supports:
- breakpoints by PC
- watchpoints by memory read/write address
- single-step mode

This repo does not include a full interactive UI debugger; it's the core API only.

## Logging
Configurable log levels (trace, debug, info, warn, error) with optional file output and timestamps. See `pox/log.hpp` for API.

## Test Suite
Unit tests for core utilities (CRC, ROM container, bitops, etc.) and smoke tests for CPU decode. See `tests/` directory.

## Debugging Workflow
1. **Enable Trace/Debugger**
   - Set `Config.enable_trace` or `Config.enable_debugger` in your emulator frontend or test harness.
2. **Run Frame/Step**
   - Use `Machine::run_frame()` or step instructions manually in a test harness.
3. **Inspect Trace**
   - Dump the trace buffer to a text file for analysis or diffing.
4. **Set Breakpoints/Watchpoints**
   - Use the Debugger API to pause execution at specific PCs or on memory access.
5. **Analyze Logs**
   - Review logs for warnings, errors, or info about device state and execution flow.

## Example: Enabling Trace
```cpp
pox::Config cfg;
cfg.enable_trace = true;
pox::Machine m(cfg);
// ... load ROM, run frame ...
// Dump trace:
m.impl_->trace.dump_text("trace.txt");
```

## Example: Setting a Breakpoint
```cpp
m.impl_->dbg.set_enabled(true);
m.impl_->dbg.add_breakpoint(0x1234);
```

## Tips
- Use trace diffing to compare emulator output with known-good runs.
- Watch for unexpected memory writes or jumps (often bugs or unimplemented opcodes).
- Use the CLI tools to inspect and validate save files and ROMs.

# POX Clone Debugging Guide

## Debugging Features
- Console debug output for game state, events, and errors
- Framebuffer summary (non-black pixel count)
- ROM load status and error messages
- Creature, biome, combat, and equipment debug logs
- Procedural world generation logs
- SDL event and input logs
- Save/load state debug output

## How to Enable Debugging
- Set `pox::log::set_config({pox::log::Level::Debug, true, true, ""});` in main.cpp
- Use `std::printf` or `std::cout` for custom debug messages
- Add debug logs in game logic, creature, biome, combat, and equipment functions

## Debugging Tips
- Check console output for errors and state changes
- Use assertions in tests for validation
- Add debug overlays in SDL renderer for visual feedback
- Log all critical events: creature actions, combat, world changes, menu selections
- Use CSV data tables for debugging interactions and conditions

## Example Debug Output
```
[DEBUG] Attempting to load ROM: roms/demo_menu_toggle.poxr
[DEBUG] ROM load result: 1
[DEBUG] Framebuffer is all black
[DEBUG] Creature spawned: Hero
[DEBUG] Combat: Hero attacks Monster for 10 damage
[DEBUG] Procedural world generated!
```

---

For advanced debugging, see docs/DEBUGGING.md and add custom logs in your code.

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

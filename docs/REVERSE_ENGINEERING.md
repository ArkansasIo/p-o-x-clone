# Reverse Engineering Guide (Practical)

## 1. Legal Note
Only dump hardware/ROMs you own. Do not redistribute proprietary ROMs.

## 2. Immediate Workflow
### A) Identify CPU & Vectors
1. Open ROM in Ghidra/IDA.
2. Look for reset/startup code (common patterns: init loops, memset, IO writes).
3. Identify interrupt vectors (if present): table of addresses near ROM start/end.

### B) Identify Memory Map via Instrumentation
1. Add logging to Bus `read8/write8`.
2. Record frequency of writes by address.
3. Correlate bursts to frame boundaries:
   - Likely VRAM region has dense repeating writes.
4. Identify input polling:
   - Repeated reads from a stable IO address.

### C) Identify LCD/VRAM Encoding
- Look for patterns of bitplane operations or tile loops.
- Compare VRAM writes with visible pixel output by rendering candidate formats.

## 3. Trace-Based Discovery
- Enable trace mode and dump text.
- Search for repeated instruction sequences that:
  - read input register
  - update game state in RAM
  - write VRAM / LCD regs

## 4. Minimal Patches That Help
- Add a "watch region" in Bus for candidate IO addresses.
- Add VRAM dump per frame to file for offline analysis.

## 5. Deliverables to Converge Quickly
- Partial opcode list
- Confirmed IO register addresses
- LCD width/height and VRAM layout

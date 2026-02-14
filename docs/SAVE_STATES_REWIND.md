# Save States & Rewind (Design + Integration Plan)

## 1. Save State Contents
A save state must capture all deterministic state:
- CPU registers + internal latches
- RAM + VRAM
- Timer state (DIV/TIMA/TMA/TAC + accumulators)
- Audio state (phase, period, enable, volume, queued samples optional)
- Cartridge SRAM (optional, or treat separately)

## 2. File Format
Use a versioned binary blob:
- Magic 'PXS0'
- Version u32
- Sections: CPU, RAM, VRAM, TIMER, AUDIO, CART

## 3. Rewind
- Maintain a ring buffer of save states (e.g., 120 frames = ~2 seconds at 60 FPS)
- Snapshot cadence:
  - Every frame (best) or every N frames (space-saving)
- Restore on rewind step:
  - Load state, then run 0 frames (immediate)

## 4. Integration Points
- Add `Machine::save_state()` and `Machine::load_state()`
- Add `Machine::rewind_step()` if ring buffer enabled
- Add CLI hotkeys in SDL frontend (example):
  - F5 quicksave
  - F8 quickload
  - R rewind while held

## 5. Determinism Notes
- Avoid using wall-clock inside core.
- Audio queueing can be reconstructed; store only generator phase.

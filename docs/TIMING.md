# Timing

The core uses:
- `cpu_hz` (CPU frequency)
- `frame_hz` (video refresh, default 60)
- `sample_rate` (audio sample rate)

`Clock` computes a per-frame cycle budget with remainder accumulation to prevent drift.

This is the correct pattern for emulators even before you know the exact PO-X crystal/oscillator.

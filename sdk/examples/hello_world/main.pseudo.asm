; PSEUDO-ASSEMBLY (placeholder)
; Fill VRAM with 0xFF so the display shows bright pixels.

START:
  A <- $FF
  addr <- VRAM_BASE
LOOP:
  [addr] <- A
  addr <- addr + 1
  if addr < VRAM_BASE + $0800 goto LOOP
HALT:
  goto HALT

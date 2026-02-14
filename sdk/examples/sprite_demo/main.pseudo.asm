; PSEUDO-ASSEMBLY (placeholder)
; Fill VRAM with repeating 2bpp pattern to show stripes.
START:
  A <- $E4   ; bits 11 10 01 00 pattern
  addr <- VRAM_BASE
LOOP:
  [addr] <- A
  addr <- addr + 1
  if addr < VRAM_BASE + $0800 goto LOOP
HALT:
  goto HALT

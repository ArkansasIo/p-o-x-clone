; PSEUDO-ASSEMBLY (placeholder)
; Enable audio and set period/volume.
START:
  [AUDIO_BASE + 0] <- 1      ; enable
  [AUDIO_BASE + 1] <- 128    ; volume
  [AUDIO_BASE + 2] <- 100    ; period lo
  [AUDIO_BASE + 3] <- 0      ; period hi
HALT:
  goto HALT

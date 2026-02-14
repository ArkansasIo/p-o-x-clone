; PO-X SDK Hardware Defines (PLACEHOLDER)
; Replace addresses when real memory map is confirmed.

VRAM_BASE   equ $8000
IO_BASE     equ $8800

; IO sub-blocks (offsets)
LCD_BASE    equ IO_BASE + $000
INPUT_BASE  equ IO_BASE + $100
TIMER_BASE  equ IO_BASE + $200
AUDIO_BASE  equ IO_BASE + $300
POWER_BASE  equ IO_BASE + $400

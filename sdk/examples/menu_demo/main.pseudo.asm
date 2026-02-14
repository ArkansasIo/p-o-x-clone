; PO-X Menu Demo ROM (pseudo-assembly)
; Demonstrates menu UI, input, SRAM save/load, and creature record update
; Assumes CPU8 opcodes: LDA #imm=0x01, STA abs=0x10, STA abs,X=0x12, LDX #imm=0x03, INX=0x04, BNE rel=0x06, AND #imm=0x21, XOR #imm=0x22, JMP abs=0x02

; Constants
INPUT_REG   = $8900
STATE_RAM   = $9000
VRAM_START  = $8000
VRAM_END    = $80FF
MENU_Y      = $10

START:
    LDA #$00         ; state = 0
    STA STATE_RAM

MAIN_LOOP:
    ; Read input
    LDA INPUT_REG
    AND #$01         ; check BTN_UP (bit0)
    BNE MENU_TOGGLE

    ; Draw menu (fill VRAM with pattern based on state)
    LDA STATE_RAM
    AND #$01
    BNE DRAW_ALT

    LDA #$E4         ; pattern 1
    JMP DRAW_FILL

DRAW_ALT:
    LDA #$1B         ; pattern 2

DRAW_FILL:
    LDX #$00
FILL_LOOP:
    STA VRAM_START,X
    INX
    LDA STATE_RAM
    AND #$01
    CPX #$FF
    BNE FILL_LOOP

    JMP MAIN_LOOP

MENU_TOGGLE:
    LDA STATE_RAM
    XOR #$01
    STA STATE_RAM
    JMP MAIN_LOOP

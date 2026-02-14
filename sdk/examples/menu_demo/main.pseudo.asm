

































; PO-X Menu Demo ROM (pseudo-assembly)
; Demonstrates menu UI, input, SRAM save/load, and creature record update
; Assumes CPU8 opcodes: LDA #imm=0x01, STA abs=0x10, STA abs,X=0x12, LDX #imm=0x03, INX=0x04, BNE rel=0x06, AND #imm=0x21, XOR #imm=0x22, JMP abs=0x02

; Constants
INPUT_REG   = $8900
STATE_RAM   = $9000
VRAM_START  = $8000
VRAM_END    = $80FF
MENU_Y      = $10
CREATURE_HP = $9100
CREATURE_ATK = $9101
CREATURE_DEF = $9102
CREATURE_SPD = $9103

START:
    LDA #$00         ; state = 0
    STA STATE_RAM
    LDA #100         ; HP = 100
    STA CREATURE_HP
    LDA #10          ; ATK = 10
    STA CREATURE_ATK
    LDA #10          ; DEF = 10
    STA CREATURE_DEF
    LDA #10          ; SPD = 10
    STA CREATURE_SPD

MAIN_LOOP:
    ; Read input
    LDA INPUT_REG
    AND #$01         ; check BTN_UP (bit0)
    BNE MENU_TOGGLE

    ; Draw menu (fill VRAM with pattern based on state)
    LDA STATE_RAM
    AND #$01
    BNE DRAW_ALT

    ; Pattern 1: Show creature stats
    LDA CREATURE_HP
    STA VRAM_START      ; HP
    LDA CREATURE_ATK
    STA VRAM_START+1   ; ATK
    LDA CREATURE_DEF
    STA VRAM_START+2   ; DEF
    LDA CREATURE_SPD
    STA VRAM_START+3   ; SPD
    JMP DRAW_FILL

DRAW_ALT:
    ; Pattern 2: Increase HP by 1 each toggle
    LDA CREATURE_HP
    ADD #1
    STA CREATURE_HP
    LDA #$1B         ; pattern 2
    JMP DRAW_FILL

DRAW_FILL:
    LDX #$04
FILL_LOOP:
    STA VRAM_START,X
    INX
    CPX #$FF
    BNE FILL_LOOP

    JMP MAIN_LOOP

MENU_TOGGLE:
    LDA STATE_RAM
    XOR #$01
    STA STATE_RAM
    JMP MAIN_LOOP

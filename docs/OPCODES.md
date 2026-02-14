# CPU Opcodes (PLACEHOLDER)

`CPU8` currently implements a tiny demo instruction set:

- 0x00: NOP (2 cycles)
- 0x01: LDA #imm (2 cycles)
- 0x02: JMP abs16 (3 cycles)
- 0x10: STA abs16 (4 cycles)   (writes A to memory)
- 0x11: LDA abs16 (4 cycles)
- 0x20: ADD #imm (2 cycles)    (A = A + imm)
- 0x30: BRK (2 cycles)         (sets halted flag)

This is **not** the real PO-X ISA. It is only to keep the scaffold runnable.

When you know the real ISA, replace:
- decode table in `src/pox/hw/cpu8.cpp`
- disassembler formatting in `src/pox/debug/disasm.cpp`

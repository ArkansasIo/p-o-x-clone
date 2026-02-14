# PO-X Clone CPU8 Instruction Set (ISA)

This document describes the placeholder CPU8 instruction set used in the PO-X clone project. Update as you reverse-engineer the real PO-X CPU.

## Supported Instructions
| Opcode | Mnemonic      | Description                  |
|--------|--------------|------------------------------|
| 0x00   | NOP          | No operation                 |
| 0x01   | LDA #imm8    | Load A with immediate        |
| 0x02   | JMP abs16    | Jump to absolute address     |
| 0x03   | LDX #imm8    | Load X with immediate        |
| 0x04   | INX          | Increment X                  |
| 0x06   | BNE rel8     | Branch if Z==0 (relative)    |
| 0x10   | STA abs16    | Store A to absolute address  |
| 0x12   | STA abs16,X  | Store A to abs+X             |
| 0x21   | AND #imm8    | A = A & imm8                 |
| 0x22   | XOR #imm8    | A = A ^ imm8                 |

## Flags
- Z (zero) flag is set by LDX, INX, AND, XOR

## Example Usage
```
LDX #$00
LDA #$E4
FILL:
  STA $8000,X
  INX
  BNE FILL
```

## To Add (when real PO-X known)
- More addressing modes
- Interrupts
- Stack ops
- Real flag behavior
- Real opcode table

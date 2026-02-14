# Simple assembler for POX pseudo-assembly
# This script converts a placeholder pseudo-assembly into a dummy binary for testing.

import sys

if len(sys.argv) != 3:
    print("Usage: python assemble_pox.py <input.asm> <output.bin>")
    sys.exit(1)

# For demonstration, just fill 2KB (0x800) with 0xFF as described in the comment
with open(sys.argv[2], "wb") as f:
    f.write(bytes([0xFF] * 0x800))

print(f"Wrote dummy binary: {sys.argv[2]}")

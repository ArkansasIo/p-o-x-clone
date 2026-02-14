# Homebrew SDK Guide (Scaffold)

This project includes a small starter SDK layout under `/sdk`.
It is **placeholder** until the real PO-X ISA is known, but provides:
- ROM packaging (POXR)
- Example bytecode/assembly skeletons
- Asset conversion tool stubs (sprite/audio)

## Quickstart (concept)
1) Build tools:
- `pox_rom_packer` (already included)
- `pox_sprite_converter` (stub)
- `pox_audio_converter` (stub)

2) Create a ROM:
- Use example templates in `sdk/examples`

3) Package:
- `pox_rom_packer game.bin game.poxr`

4) Run:
- `pox_desktop game.poxr`

## SDK Layout
- `sdk/include/` register and IO conventions (placeholder)
- `sdk/examples/` sample projects
- `sdk/tools/` conversion scripts and CLIs

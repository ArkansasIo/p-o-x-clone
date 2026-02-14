# Save System

Cartridge SRAM is stored as:
`<save_prefix>.sav`

Example:
- `save_prefix = "saves/pox_game1"`
- save file: `saves/pox_game1.sav`

SRAM is loaded at cartridge load time if present and correct size.
SRAM is saved by calling `Cartridge::save_sram()` (front-end should do this on exit).

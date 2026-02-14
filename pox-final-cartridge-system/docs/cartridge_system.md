# POX Cartridge System Guide

This document explains the structure, tools, and workflow for building PO-X cartridges.

## Tools
- build_rom.py: Combines assets and game data into a cartridge file
- cartridge_packer.py: Packs multiple ROMs/assets into a cartridge archive
- save_slot_builder.py: Generates save slot memory files
- sprite_generator.py: Creates procedural creature sprites

## Workflow
1. Prepare assets and sprites
2. Run build_rom.py to create cartridge
3. Use cartridge_packer.py to archive multiple cartridges
4. Generate save slots with save_slot_builder.py
5. Create sprites with sprite_generator.py
6. Integrate boot animation and templates

# PO-X Creature System

This document describes the 20-byte creature record format, SRAM slotting, CRC validation, and runtime logic for the PO-X clone project.

## Creature Record Layout (20 bytes)
| Byte | Field         | Description                |
|------|--------------|----------------------------|
| 0    | head_id      | Head part index            |
| 1    | head_hp      | Head HP                    |
| 2    | body_id      | Body part index            |
| 3    | body_hp      | Body HP                    |
| 4    | tail_id      | Tail part index            |
| 5    | tail_hp      | Tail HP                    |
| 6-11 | wad_indices  | 6 WAD indices (chars/sprites) |
|12-17 | name_indices | 6 name character indices   |
|18-19 | crc16        | CRC-16 (IBM, little-endian)|

## SRAM Slotting
- Each creature record is 20 bytes.
- SRAM can store multiple slots (e.g., 8 slots = 160 bytes).
- Slot N is at offset N*20 in SRAM.

## CRC Validation
- CRC-16/IBM (poly 0xA001, init 0xFFFF) over bytes 0–17.
- Stored in bytes 18–19 (little-endian).

## Runtime Logic
- Creature state (HP, name, parts) is loaded from SRAM.
- Game loop updates age, hunger, mood, HP.
- CRC is checked on load and fixed on save.

## CLI Tool
- `dump`: Print all fields and CRC status.
- `validate`: Check CRC.
- `fixcrc`: Fix CRC and write new file.

## WAD Resources
- Sprites and name characters are indexed from a JSON file (see assets/wad/index_dev.json).

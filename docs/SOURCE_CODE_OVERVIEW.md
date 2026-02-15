# Source Code Documentation

This document describes the structure and purpose of the main source code files in the P-O-X 2001 Handheld Clone project.

## Key Source Folders
- `src/pox/maze/` — Maze, dungeon, trial, raid, tower, and world generation
- `src/pox/rpg/` — RPG/MMO logic: character, party, quest, inventory, combat
- `src/pox/db/` — SQL-like game database for creatures, items, parts, etc.
- `src/pox/universe/` — Universe, planet, and room management
- `src/pox/resource/` — Resource gathering and tech tree
- `src/pox/combat/` — Combat, world events, PvP/PvE
- `src/pox/wireless/` — Unified RF/WiFi/Internet multiplayer API
- `src/pox/config/` — Unified config system
- `firmware/`, `eeprom/`, `patches/`, `updates/` — Save, firmware, patch, and update systems

## Example Entry Point
- `examples/integration_demo.cpp` — Demonstrates integration of maze, RPG, database, and universe systems

## How to Extend
- Add new modules in `src/pox/` and corresponding headers in `include/pox/`
- Document new features in `docs/`
- See `docs/UML_OVERVIEW.md` for system relationships

## See Also
- [Game Design Overview](GAME_DESIGN_OVERVIEW.md)
- [UML Overview](UML_OVERVIEW.md)
- [Maze System](MAZE_SYSTEM.md)
- [Game Database](GAME_DATABASE.md)

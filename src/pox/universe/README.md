# Universe, Room, and Open World System

This module implements the procedural universe, planet, and multiplayer room system for the P-O-X handheld clone.

## Features
- Procedural universe and planet generation from a universe seed
- Up to 32 players per planet/room
- Room join/creation logic
- Data structures for Player, Room, Universe

## Files
- `universe.hpp` — Data structures and API
- `universe.cpp` — Implementation

## Usage Example
```cpp
#include "universe.hpp"

Universe universe;
universe.universeSeed = 123456789;
universe.planetSeeds = generatePlanets(universe.universeSeed, 128);

PlayerInfo player{1, "Alice"};
Room room = joinRoom(universe.planetSeeds[0], player);
```

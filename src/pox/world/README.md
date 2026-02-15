# World Combat, PvP, PvE, and Asynchronous Actions

This module implements world-based combat, raids, sabotage, and spy actions for the P-O-X handheld clone.

## Features
- PvP and PvE combat in world zones (planets)
- Asynchronous (offline) and synchronous (online) battles
- Raids, sabotage, and spy missions
- Deterministic combat simulation for async battles
- Battle logs and notifications

## Files
- `combat.hpp` — Data structures and API
- `combat.cpp` — Implementation

## Usage Example
```cpp
#include "combat.hpp"

PlayerInfo attacker{1, "Alice"};
PlayerInfo defender{2, "Bob"};
WorldZone zone{123456, {2}, {1}, {}};
CombatResult result = simulateCombat(attacker, defender, zone);
std::cout << result.log;
```

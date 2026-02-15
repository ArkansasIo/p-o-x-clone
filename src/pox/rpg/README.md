# RPG & MMORPG Features and Game Logic

This module implements core RPG and MMO features for the P-O-X handheld clone.

## Features
- Character creation, leveling, stats, and equipment
- Party system
- Quest system
- MMO-ready data structures and functions

## Files
- `character.hpp/cpp` — Character logic
- `party.hpp/cpp` — Party logic
- `quest.hpp/cpp` — Quest logic

## Usage Example
```cpp
#include "character.hpp"
#include "party.hpp"
#include "quest.hpp"

Character alice = createCharacter("Alice");
gainExperience(alice, 250);
Party party;
joinParty(alice, party);
startQuest(alice, 1);
completeQuest(alice, 1);
```

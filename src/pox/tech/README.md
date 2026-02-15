# Technology and Research Tree System

This module implements the tech/research tree for the P-O-X handheld clone.

## Features
- 1–150 unique technologies
- Unlocks new abilities, upgrades, and world features
- Dependencies and progression logic

## Files
- `tech.hpp` — Data structures and API
- `tech.cpp` — Implementation

## Usage Example
```cpp
#include "tech.hpp"

PlayerTechTree techTree;
// Populate techTree.techs with 150 techs...
techTree.unlockTech(42);
bool unlocked = techTree.isUnlocked(42);
```

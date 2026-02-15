# Maze Exploration and Infector System

- Explore up to 999 procedurally generated maze levels.
- Each maze is unique per generation (seeded by level and base seed).
- Over 600 collectible body parts, weapons, armor, and more.
- Your Infector can discover, capture, and equip new parts and items.
- Each maze contains loot, enemies, and secrets.

## Maze System
- See `pox/maze/maze.hpp` and `pox/maze/maze.cpp` for code.
- Mazes are generated using DFS and a unique seed for each level.
- Each cell can contain items, enemies, or events.

## Infector System
- The Infector is your main creature/avatar.
- Can equip captured parts, weapons, and armor.
- Each part grants new abilities or stats.
- Capture system integrates with RPG, combat, and resource systems.

## Example Usage
```cpp
#include "pox/maze/maze.hpp"

// Generate and print a maze
auto maze = pox::maze::generateMaze(42, 16, 16, 0xDEADBEEF);
std::cout << pox::maze::describeMaze(maze);
```

---

- Extend the system to add loot, enemy placement, and Infector abilities as needed.

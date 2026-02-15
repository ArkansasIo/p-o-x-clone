# POX Clone - Modular RPG/MMORPG Framework

## Overview
POX Clone is a modular RPG/MMORPG engine featuring:
- Creature, combat, and equipment frameworks
- Biome, zone, counter, and condition systems
- Procedural world generation
- Survival mechanics and stat management
- SDL2-based GUI and PI interface
- CSV-driven data tables
- Test-driven development

## Gameplay Loop Integration
The main gameplay loop is managed by the `pox::game::GameLogic` class:
- `tick()`: Advances the game state, handles creature survival, combat, and world events
- `spawnCreature(name)`: Adds new creatures to the world
- `handleCombat(attackerId, defenderId)`: Resolves combat between creatures
- `equipItem(creatureId, item)`: Equips items and updates stats
- `applyBuff`/`applyDebuff`: Applies buffs/debuffs to creatures
- `updateBiome`/`updateZone`: Changes biome/zone context
- `handleSurvivalCounters`: Manages survival stats and conditions
- `generateProceduralWorld()`: Creates new world layouts

## Next Steps: Gameplay Loop Implementation

To further expand the gameplay loop, integrate the following in your main executable:

1. Instantiate `pox::game::GameLogic`.
2. Call `tick()` in your main loop to advance game state.
3. Use `spawnCreature`, `handleCombat`, `equipItem`, and other methods to drive gameplay.
4. Connect GUI/PI interface for player input and display.

### Example Main Loop (C++)

```cpp
#include "pox/game/game_logic.hpp"
#include <SDL.h>

int main(int argc, char* argv[]) {
    pox::game::GameLogic game;
    game.generateProceduralWorld();
    game.spawnCreature("Hero");
    game.spawnCreature("Monster");

    bool running = true;
    while (running) {
        // Handle SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            // ...handle input, update game state...
        }
        game.tick();
        // ...render, update GUI...
    }
    return 0;
}
```

## Feature Expansion
- Modular creature system: Add new types, races, and abilities
- Biome/zone/counter/condition: Expand environmental and survival logic
- Equipment and buffs: Add new items, effects, and stat modifiers
- Procedural world: Enhance generation algorithms and event systems

## Testing
- All features are covered by unit tests in `tests/`
- Run tests with `build/tests/Debug/pox_tests.exe`


## Build Instructions

1. Install [SDL2](https://www.libsdl.org/) development libraries.
2. Clone this repository.
3. Run CMake to configure and build:
    ```sh
    cmake -S . -B build
    cmake --build build
    ```
4. Run the desktop SDL app from `build/apps/desktop_sdl/`.

## Directory Structure

- `src/` - Core engine source code
- `apps/` - Example and platform-specific frontends
- `assets/` - Game assets (ROMs, fonts, packs, skins)
- `docs/` - Technical and design documentation
- `tools/` - Asset and ROM tools
- `tests/` - Unit and regression tests

## Contributing

Contributions are welcome! Please see the [docs/README.md](docs/README.md) for documentation and guidelines.

## Contributing
- Add new features via modular headers and source files
- Expand CSV data tables for biomes, zones, counters, and conditions
- Integrate new gameplay logic in `GameLogic`

## License
See LICENSE for details.

---
For detailed architecture, see `docs/ARCHITECTURE.md` and related docs.



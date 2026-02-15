# POX Game System UML Overview

```mermaid
classDiagram
    class MazeLevel {
        +uint32_t levelIndex
        +uint64_t seed
        +int width
        +int height
        +MazeType type
        +string theme
        +grid: MazeCell[][]
    }
    class Character {
        +uint32_t id
        +string name
        +int level
        +int exp
        +int hp, maxHp
        +int attack, defense, speed, special
        +equipment: uint32_t[]
        +skills: uint32_t[]
    }
    class DBTable {
        +string name
        +DBColumn[] columns
        +DBRow[] rows
    }
    class Universe {
        +uint64_t universeSeed
        +planetSeeds: uint64_t[]
    }
    class Room {
        +uint32_t roomID
        +string name
        +PlayerInfo[] players
        +uint32_t planetSeed
    }
    MazeLevel --> "*" Character : contains
    Universe --> "*" Room : has
    Room --> "*" Character : contains
    DBTable --> "*" Character : stores
```

---

- See docs/ARCHITECTURE.md for more details on system relationships.
- See docs/GAME_DATABASE.md, docs/MAZE_SYSTEM.md, and docs/CONFIG_SYSTEM.md for subsystem documentation.

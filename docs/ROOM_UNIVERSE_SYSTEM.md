# P-O-X Handheld — Room, Open World, and Universe Seed System

## 1. Room System (1–32 Players)
### Overview
- Supports multiplayer rooms/lobbies for up to 32 players
- Each room can be a battle, trade, or social zone
- Players can join/leave rooms dynamically
- Room state is synchronized over RF/WiFi/Internet

### Room Data Structure (C++)
```cpp
struct PlayerInfo {
  uint8_t id;
  std::string name;
  // Player state, position, etc.
};

struct Room {
  uint32_t roomID;
  std::string name;
  std::vector<PlayerInfo> players; // up to 32
  uint32_t planetSeed; // For open world context
  // Room/game state
};
```

### Room Protocol
- Create room (host)
- Join room (peer)
- Leave room
- Broadcast room state
- Sync player actions

---

## 2. Open World & Universe Seed System
### Overview
- Procedurally generated universe (like No Man's Sky)
- Each planet/world is generated from a unique seed
- Each planet can host 1–32 players in a room
- Universe seed determines all planet seeds

### Universe & Planet Generation
```cpp
struct Universe {
  uint64_t universeSeed;
  std::vector<uint64_t> planetSeeds;
};

// Generate N planets from universe seed
std::vector<uint64_t> generatePlanets(uint64_t universeSeed, int numPlanets) {
  std::vector<uint64_t> seeds;
  std::mt19937_64 rng(universeSeed);
  for (int i = 0; i < numPlanets; ++i) {
    seeds.push_back(rng());
  }
  return seeds;
}
```

### Planet Instance
- Each planet is a unique open world, generated from its seed
- Players on the same planet/seed share the same world
- Each planet can have its own room (1–32 players)

---

## 3. Example: Joining a Planet Room
```cpp
// 1. Select planet (by index or seed)
uint64_t planetSeed = universe.planetSeeds[planetIndex];
// 2. Join or create room for that planet
Room planetRoom = joinRoom(planetSeed);
// 3. Sync world state and player actions
```

---

## 4. Open World Synchronization
- World state is synchronized among all players in the room
- Use delta updates for efficiency
- Authority can be host or distributed

---

## 5. Universe Seed Persistence
- Universe seed is saved per device or per session
- Allows for persistent, shared universe across all players
- Changing the universe seed creates a new universe

---

## 6. Scalability & Future Extensions
- Shard universe into galaxies for more than 32 players per planet
- Add cross-planet travel, trading, and events
- Integrate with cloud for persistent universe state

---

## 7. References
- [Procedural Generation (Wikipedia)](https://en.wikipedia.org/wiki/Procedural_generation)
- [No Man's Sky Procedural Universe](https://www.gamasutra.com/view/news/277451/)

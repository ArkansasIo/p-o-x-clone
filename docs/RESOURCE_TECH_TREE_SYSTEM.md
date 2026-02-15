# P-O-X Handheld — Resource, Gathering, and Tech/Research Tree System

## 1. Overview
This system enables:
- Resource gathering and management
- Technology and research tree progression (1–150 techs)
- Unlocking new abilities, upgrades, and world features
- Integration with world, combat, and multiplayer systems

---

## 2. Resource System
- **Resource Types:** Minerals, energy, DNA, artifacts, etc.
- **Gathering:** Players collect resources from worlds, battles, or events
- **Storage:** Per-player inventory, world/zone stockpiles

### Resource Data Structure
```cpp
struct Resource {
  uint8_t id;
  std::string name;
  int quantity;
};

struct PlayerResources {
  std::vector<Resource> resources;
  void addResource(uint8_t id, int amount);
  bool spendResource(uint8_t id, int amount);
};
```

---

## 3. Gathering System
- **Manual:** Player actions (explore, mine, battle)
- **Automated:** Drones, buildings, or world events
- **PvP/PvE:** Steal or win resources from others

---

## 4. Tech/Research Tree (1–150)
- **Tech Tree:** 150 unique technologies
- **Unlocks:** New abilities, upgrades, world access, combat powers
- **Dependencies:** Each tech can require others
- **Progression:** Spend resources to unlock techs

### Tech Data Structure
```cpp
struct Tech {
  uint16_t id;
  std::string name;
  std::string description;
  std::vector<uint16_t> prerequisites;
  bool unlocked;
};

struct PlayerTechTree {
  std::vector<Tech> techs;
  void unlockTech(uint16_t id);
  bool isUnlocked(uint16_t id) const;
};
```

---

## 5. Example: Unlocking a Tech
```cpp
PlayerResources resources;
PlayerTechTree techTree;
uint16_t techID = 42;
if (resources.spendResource(1, 100) && techTree.isUnlocked(10)) {
  techTree.unlockTech(techID);
}
```

---

## 6. Integration
- Tech unlocks can enable new resource types, gathering methods, or combat powers
- Research progress can be shared or competed for in multiplayer

---

## 7. Extensibility
- Add tech categories (combat, science, social, etc.)
- Add world/planet-specific techs
- Add tech trading or espionage

---

## 8. References
- [Tech Tree Design (Gamasutra)](https://www.gamedeveloper.com/design/designing-better-tech-trees)
- [Resource Management in Games](https://en.wikipedia.org/wiki/Resource_management_(video_games))

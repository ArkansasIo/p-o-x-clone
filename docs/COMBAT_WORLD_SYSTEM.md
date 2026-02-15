# P-O-X Handheld — PvP, PvE, World Combat, and Asynchronous Interaction System

## 1. Overview
This system enables:
- PvP (player vs player) and PvE (player vs environment) combat
- World-based offence/defence, raids, sabotage, and spy actions
- Asynchronous (offline) and synchronous (online) interactions
- Combat and world events even when players are offline

---

## 2. World Combat Zones
- Each planet/world can be a combat zone
- Players can attack, defend, raid, or spy on others
- Zones can be PvP-enabled, PvE-only, or mixed

### Zone Data Structure
```cpp
struct WorldZone {
  uint64_t planetSeed;
  std::vector<uint32_t> defendingPlayers;
  std::vector<uint32_t> attackingPlayers;
  std::vector<uint32_t> npcEnemies; // PvE
  // Zone state: resources, defences, etc.
};
```

---

## 3. PvP and PvE Combat
- **PvP:** Direct or asynchronous battles between players
- **PvE:** Battles against AI-controlled enemies or world events
- **Combat Types:**
  - Real-time (when both players online)
  - Asynchronous (attack/defend while offline)
  - Raids, sabotage, and spy missions

### Combat Flow
1. Player enters a world/zone
2. Can choose to attack, defend, raid, or spy
3. If target is online, real-time combat
4. If target is offline, resolve asynchronously (simulate battle)
5. Update world/zone state and notify players

---

## 4. Asynchronous Actions
- **Raids:** Attack another player's base/resources while they are offline
- **Sabotage:** Attempt to disable defences or steal info
- **Spy:** Gather intel on enemy players or zones
- **Defence:** Set up AI or player-controlled defences

---

## 5. Combat Resolution
- Use deterministic combat simulation for async battles
- Store battle logs and outcomes for review
- Allow players to set defence strategies and traps

### Example: Combat Simulation
```cpp
struct CombatResult {
  bool attackerWin;
  int resourcesStolen;
  std::string log;
};

CombatResult simulateCombat(const PlayerInfo& attacker, const PlayerInfo& defender, const WorldZone& zone);
```

---

## 6. Notifications & Logs
- Players receive notifications of attacks, raids, and spy actions
- Battle logs are stored for review
- Option to replay or counter-attack

---

## 7. Security & Fairness
- Anti-cheat: Server-authoritative combat resolution
- Rate limits on raids/spy actions
- Balanced rewards and penalties

---

## 8. Extensibility
- Add alliances, world events, and territory control
- Integrate with universe/room system for persistent world warfare

---

## 9. References
- [Asynchronous Multiplayer Design](https://www.gamasutra.com/view/feature/130663/)
- [PvP and PvE Game Design](https://en.wikipedia.org/wiki/Player_versus_player)

// Combat and world system
#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace pox::combat {

struct WorldZone {
    uint64_t planetSeed;
    std::vector<uint32_t> defendingPlayers;
    std::vector<uint32_t> attackingPlayers;
    std::vector<uint32_t> npcEnemies;
};

struct CombatResult {
    bool attackerWin;
    int resourcesStolen;
    std::string log;
};

CombatResult simulateCombat(const WorldZone& zone, uint32_t attackerId, uint32_t defenderId);

} // namespace pox::combat

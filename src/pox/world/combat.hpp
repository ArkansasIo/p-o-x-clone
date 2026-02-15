#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "../universe/universe.hpp"

struct WorldZone {
    uint64_t planetSeed;
    std::vector<uint32_t> defendingPlayers;
    std::vector<uint32_t> attackingPlayers;
    std::vector<uint32_t> npcEnemies;
    // Add zone state: resources, defences, etc.
};

struct CombatResult {
    bool attackerWin;
    int resourcesStolen;
    std::string log;
};

CombatResult simulateCombat(const PlayerInfo& attacker, const PlayerInfo& defender, const WorldZone& zone);

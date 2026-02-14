// Main game logic header for RPG/MMORPG
#pragma once
#include "creature_extended.hpp"
#include "biome_framework.hpp"
#include <vector>
#include <string>

namespace pox::game {

class GameLogic {
public:
    GameLogic();
    void tick(); // Main game loop tick
    void spawnCreature(const std::string& name);
    void handleCombat(int attackerId, int defenderId);
    void equipItem(int creatureId, const Equipment& item);
    void applyBuff(int creatureId, const Buff& buff);
    void applyDebuff(int creatureId, const Buff& debuff);
    void updateBiome(const pox::world::Biome& biome);
    void updateZone(const pox::world::Zone& zone);
    void handleSurvivalCounters(int creatureId);
    void generateProceduralWorld();

    std::vector<Creature> creatures;
    pox::world::Biome currentBiome;
    pox::world::Zone currentZone;
};

} // namespace pox::game

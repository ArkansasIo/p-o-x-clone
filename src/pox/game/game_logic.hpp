// Header for main game logic
// Header for main game logic
#pragma once
#include <vector>
#include <string>
#include "creature_db.hpp"
#include "creature_extended.hpp"
#include "main_character.hpp"
#include "settings.hpp"
#include "wad_resources.hpp"
#include "zones.hpp"
#include "continents.hpp"
#include "kingdoms.hpp"
#include "rpg_systems.hpp"
#include "../world/biome_framework.hpp"

namespace pox {
namespace game {

class GameLogic {
public:
    // Inventory and item management
    void pickupItem(int creatureId, const Equipment& item);
    bool equipFromInventory(int creatureId, const std::string& itemName);
    bool useHealingItemFromInventory(int creatureId, const std::string& itemName);
    GameLogic();
    void tick();
    void spawnCreature(const std::string& name);
    void handleCombat(int attackerId, int defenderId);
    void equipItem(int creatureId, const Equipment& item);
    void equipArmor(int creatureId, const Equipment& armor);
    void equipShield(int creatureId, const Equipment& shield);
    void useHealingItem(int creatureId, const Equipment& item);
    void applyBuff(int creatureId, const Buff& buff);
    void applyDebuff(int creatureId, const Buff& debuff);
    void updateBiome(const pox::world::Biome& biome);
    void updateZone(const pox::world::Zone& zone);
    void handleSurvivalCounters(int creatureId);
    void generateProceduralWorld();

private:
    std::vector<Creature> creatures;
    pox::world::Biome currentBiome;
    pox::world::Zone currentZone;
};

} // namespace game
} // namespace pox

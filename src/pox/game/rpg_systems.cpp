#include "rpg_systems.hpp"
#include <sstream>

namespace pox {
namespace game {

void LevelSystem::level_up() {
    if (current_level < max_level) ++current_level;
}

void LevelSystem::set_level(int lvl) {
    if (lvl >= 1 && lvl <= max_level) current_level = lvl;
}

void RPGSystems::initialize() {
    // Create 20 dungeons
    for (int i = 1; i <= 20; ++i) {
        std::ostringstream name;
        name << "Dungeon " << i;
        std::ostringstream desc;
        desc << "Description for Dungeon " << i;
        dungeons.push_back({name.str(), desc.str(), i});
    }
    // Create 15 trials
    for (int i = 1; i <= 15; ++i) {
        std::ostringstream name;
        name << "Trial " << i;
        std::ostringstream desc;
        desc << "Description for Trial " << i;
        trials.push_back({name.str(), desc.str(), i});
    }
    // Create 10 raids
    for (int i = 1; i <= 10; ++i) {
        std::ostringstream name;
        name << "Raid " << i;
        std::ostringstream desc;
        desc << "Description for Raid " << i;
        raids.push_back({name.str(), desc.str(), i*10, 8 + i});
    }
    level_system.current_level = 1;
}

} // namespace game
} // namespace pox

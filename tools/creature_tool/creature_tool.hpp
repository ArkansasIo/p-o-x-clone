// Creature tool header for creature management utilities
#pragma once
#include <string>
#include <vector>
#include "pox/game/creature_extended.hpp"

namespace pox_tool {

class CreatureTool {
public:
    CreatureTool();
    void load(const std::string& filename);
    void save(const std::string& filename);
    void addCreature(const pox::game::Creature& creature);
    std::vector<pox::game::Creature> creatures;
};

} // namespace pox_tool

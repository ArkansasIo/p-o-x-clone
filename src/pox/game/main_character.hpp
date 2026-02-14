// Main character header
#pragma once
#include "creature_extended.hpp"
#include <string>

namespace pox {
namespace game {

class MainCharacter : public Creature {
public:
    MainCharacter();
    void setName(const std::string& name);
    void setType(Type type);
    void setRace(Race race);
    void setAttributes(int str, int agi, int int_, int cha, int end, int wis, int per);
};

} // namespace game
} // namespace pox

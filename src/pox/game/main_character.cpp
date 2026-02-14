// Main character/player implementation for POX
#include "main_character.hpp"

namespace pox::game {

MainCharacter::MainCharacter()
    : Creature("POX", Type::Humanoid, SubType::None, Race::Human) {
    // Default attributes for main character
    setAttributes(12, 12, 12, 12, 12, 12, 12);
}

void MainCharacter::setName(const std::string& name) {
    this->name = name;
}

void MainCharacter::setType(Type type) {
    this->type = type;
}

void MainCharacter::setRace(Race race) {
    this->race = race;
}

void MainCharacter::setAttributes(int str, int agi, int int_, int cha, int end, int wis, int per) {
    attributes[AttributeType::Strength] = str;
    attributes[AttributeType::Agility] = agi;
    attributes[AttributeType::Intelligence] = int_;
    attributes[AttributeType::Charisma] = cha;
    attributes[AttributeType::Endurance] = end;
    attributes[AttributeType::Wisdom] = wis;
    attributes[AttributeType::Perception] = per;
    recalculate_stats();
}

} // namespace pox::game

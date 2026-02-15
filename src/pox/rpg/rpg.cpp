// RPG/MMO core logic (stub)
#include "pox/rpg/rpg.hpp"
#include <iostream>

namespace pox::rpg {

Character createCharacter(const std::string& name) {
    Character c{0, name, 1, 0, 100, 100, 10, 10, 10, 10, {}, {}};
    std::cout << "[RPG] Created character: " << name << "\n";
    return c;
}
void gainExperience(Character& c, int amount) {
    c.exp += amount;
    if (c.level < 999 && c.exp >= 100 * c.level) { // Example exp curve
        levelUp(c);
    }
    c.clampLevel();
}
void levelUp(Character& c) {
    if (c.level < 999) ++c.level;
    c.exp = 0;
    c.maxHp += 10;
    c.hp = c.maxHp;
    c.clampLevel();
}
void equipItem(Character& c, uint32_t itemId) {
    c.equipment.push_back(itemId);
}
void startQuest(Character& c, uint32_t questId) {
    std::cout << "[RPG] Start quest " << questId << "\n";
}
void completeQuest(Character& c, uint32_t questId) {
    std::cout << "[RPG] Complete quest " << questId << "\n";
}
void joinParty(Character& c, Party& party) {
    party.members.push_back(c);
}
void tradeItems(Character& a, Character& b, uint32_t itemId, int amount) {
    std::cout << "[RPG] Trade item " << itemId << "\n";
}
void sendMessage(uint32_t fromId, uint32_t toId, const std::string& msg) {
    std::cout << "[RPG] Message from " << fromId << " to " << toId << ": " << msg << "\n";
}

} // namespace pox::rpg

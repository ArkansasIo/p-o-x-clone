// RPG/MMO core data structures
#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace pox::rpg {

struct Character {
    uint32_t id;
    std::string name;
    int level;
    int exp;
    int hp, maxHp;
    int attack, defense, speed, special;
    std::vector<uint32_t> equipment;
    std::vector<uint32_t> skills;
};

struct Party {
    std::vector<Character> members;
};

struct Quest {
    uint32_t id;
    std::string name;
    std::string description;
    bool completed;
};

Character createCharacter(const std::string& name);
void gainExperience(Character& c, int amount);
void levelUp(Character& c);
void equipItem(Character& c, uint32_t itemId);
void startQuest(Character& c, uint32_t questId);
void completeQuest(Character& c, uint32_t questId);
void joinParty(Character& c, Party& party);
void tradeItems(Character& a, Character& b, uint32_t itemId, int amount);
void sendMessage(uint32_t fromId, uint32_t toId, const std::string& msg);

} // namespace pox::rpg

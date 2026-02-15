#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Character {
    uint32_t id;
    std::string name;
    int level;
    int exp;
    int hp, maxHp;
    int attack, defense, speed, special;
    std::vector<uint32_t> equipment;
    std::vector<uint32_t> skills;
    // Inventory, quests, etc.
};

Character createCharacter(const std::string& name);
void gainExperience(Character& c, int amount);
void levelUp(Character& c);
void equipItem(Character& c, uint32_t itemId);

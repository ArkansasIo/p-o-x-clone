#include "character.hpp"
#include <algorithm>

Character createCharacter(const std::string& name) {
    Character c;
    c.id = 0; // Assign unique ID in real system
    c.name = name;
    c.level = 1;
    c.exp = 0;
    c.maxHp = c.hp = 100;
    c.attack = 10;
    c.defense = 10;
    c.speed = 10;
    c.special = 5;
    return c;
}

void gainExperience(Character& c, int amount) {
    c.exp += amount;
    while (c.exp >= c.level * 100) {
        c.exp -= c.level * 100;
        levelUp(c);
    }
}

void levelUp(Character& c) {
    ++c.level;
    c.maxHp += 10;
    c.hp = c.maxHp;
    c.attack += 2;
    c.defense += 2;
    c.speed += 1;
    c.special += 1;
}

void equipItem(Character& c, uint32_t itemId) {
    if (std::find(c.equipment.begin(), c.equipment.end(), itemId) == c.equipment.end()) {
        c.equipment.push_back(itemId);
    }
}

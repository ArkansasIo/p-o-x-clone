#include "inventory.hpp"
// Creature extended header
#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
#include "creature_record.hpp"

namespace pox {
namespace game {

enum class StatType {
    HP, MP, ATK, DEF, SPD, LUCK, EXP, LEVEL, CRIT, EVADE, RESIST, ACCURACY, ARMOR_PEN, MAGIC_PEN
};

enum class AttributeType {
    Strength, Agility, Intelligence, Charisma, Endurance, Wisdom, Perception
};

enum class BuffType {
    ATK_UP, DEF_UP, SPD_UP, HP_REGEN, MP_REGEN, CRIT_UP, EVADE_UP, RESIST_UP,
    POISON, STUN, SLOW, WEAKEN, BURN, FREEZE, CURSE
};

struct Buff {
    BuffType type;
    int value;
};


enum class EquipmentType {
    Weapon,
    Armor,
    Shield,
    Accessory,
    HealingItem
};

struct Equipment {
    std::string name;
    EquipmentType type;
    std::map<StatType, int> stat_modifiers;
    int heal_points = 0; // For healing items
};

class Creature {
public:
    enum class Type { Humanoid, Monster, Animal };
    enum class SubType { None, Warrior, Mage, Rogue, Beast, Undead };
    enum class Race { Human, Elf, Orc, Goblin, Dragon, Wolf, Bear };

    Creature(std::string name, Type type, SubType subtype, Race race);
    void apply_buff(const Buff& buff);
    void apply_debuff(const Buff& debuff);
    void equip(const Equipment& item);
    void unequip(const Equipment& item);
    void heal(int points);
    void use_healing_item(const Equipment& item);
    void recalculate_stats();

    std::string name;
    Type type;
    SubType subtype;
    Race race;
    std::array<int, 8> parts_hp;
    std::map<StatType, int> base_stats;
    std::map<StatType, int> derived_stats;
    std::map<AttributeType, int> attributes;
    std::vector<Buff> buffs;
    std::vector<Buff> debuffs;
    std::vector<Equipment> equipment;
    Equipment* armor = nullptr;
    Equipment* shield = nullptr;
    Inventory inventory;
};

class Monster : public Creature {
public:
    Monster(std::string name, SubType subtype, Race race);
    int ferocity;
};

class Animal : public Creature {
public:
    Animal(std::string name, SubType subtype, Race race);
    int tameness;
};

} // namespace game
} // namespace pox

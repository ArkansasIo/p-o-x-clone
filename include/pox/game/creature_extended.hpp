#pragma once
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <map>

namespace pox::game {
// Body part types for modular creatures
enum class BodyPartType {
    Head,
    Torso,
    ArmL,
    ArmR,
    LegL,
    LegR,
    Wing,
    Tail,
    Horn
};

class BodyPart {
public:
    BodyPartType type;
    std::string name;
    int hp;
    int defense;
    int attack;
    bool isCritical;
    BodyPart(BodyPartType type, std::string name, int hp, int defense, int attack, bool isCritical = false)
        : type(type), name(std::move(name)), hp(hp), defense(defense), attack(attack), isCritical(isCritical) {}
};

// RPG/MMORPG Stats Framework
enum class StatType {
    HP, MP, ATK, DEF, SPD, LUCK, EXP, LEVEL,
    CRIT, EVADE, RESIST, ACCURACY, ARMOR_PEN, MAGIC_PEN,
    STRENGTH, AGILITY, INTELLIGENCE, CHARISMA, ENDURANCE, WISDOM, PERCEPTION,
    FIRE_AFFINITY, WATER_AFFINITY, EARTH_AFFINITY, AIR_AFFINITY, LIGHT_AFFINITY, DARK_AFFINITY
};

enum class AttributeType {
    Strength, Agility, Intelligence, Charisma, Endurance, Wisdom, Perception
};

enum class BuffType {
    ATK_UP, DEF_UP, SPD_UP, HP_REGEN, MP_REGEN, CRIT_UP, EVADE_UP, RESIST_UP,
    POISON, STUN, SLOW, WEAKEN, BURN, FREEZE, CURSE
};

enum class EquipmentType {
    Weapon, Armor, Accessory
};

struct Buff {
    BuffType type;
    int value;
    int duration;
};

struct Equipment {
    EquipmentType type;
    std::string name;
    std::map<StatType, int> stat_modifiers;
    std::vector<Buff> buffs;
};

class Creature {
public:
    enum class Type { Generic, Monster, Animal, Humanoid, Weapon, Armor };
    enum class SubType { None, Fire, Water, Earth, Air, Magic, Undead, Beast, Machine, Plant, Insect, Dragon };
    enum class Race { None, Human, Elf, Orc, Goblin, Beastman, Undead, Dragon, Demon, Angel, Construct, Elemental };
    enum class Part { Head, Body, Tail, ArmL, ArmR, LegL, LegR, WingL, WingR, Horn, Eye, Mouth, Skin };

    Creature(std::string name, Type type, SubType subtype, Race race);
    virtual ~Creature() = default;

    std::string name;
    Type type;
    SubType subtype;
    Race race;
    std::array<int, 12> parts_hp; // 12 parts
    std::vector<BodyPart> body_parts; // Modular body parts

    // Base stats
    std::map<StatType, int> base_stats;
    // Derived stats
    std::map<StatType, int> derived_stats;
    // Attributes
    std::map<AttributeType, int> attributes;
    // Buffs/Debuffs
    std::vector<Buff> buffs;
    std::vector<Buff> debuffs;
    // Equipment
    std::vector<Equipment> equipment;

    // Methods
    void apply_buff(const Buff& buff);
    void apply_debuff(const Buff& debuff);
    void equip(const Equipment& item);
    void unequip(const Equipment& item);
    void recalculate_stats();
};

// Monster subclass
class Monster : public Creature {
public:
    Monster(std::string name, SubType subtype, Race race);
    int ferocity;
};

// Animal subclass
class Animal : public Creature {
public:
    Animal(std::string name, SubType subtype, Race race);
    int tameness;
};

} // namespace pox::game

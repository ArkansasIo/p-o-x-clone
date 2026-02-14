#include "creature_extended.hpp"
// Ensure Creature members are defined in the header and accessible here

namespace pox::game {

Creature::Creature(std::string name, Type type, SubType subtype, Race race)
    : name(std::move(name)), type(type), subtype(subtype), race(race) {
    parts_hp.fill(100);
    // Initialize base stats
        base_stats[StatType::HP] = 100;
        base_stats[StatType::MP] = 50;
        base_stats[StatType::ATK] = 10;
        base_stats[StatType::DEF] = 10;
        base_stats[StatType::SPD] = 10;
        base_stats[StatType::LUCK] = 5;
        base_stats[StatType::EXP] = 0;
        base_stats[StatType::LEVEL] = 1;
        base_stats[StatType::CRIT] = 0;
        base_stats[StatType::EVADE] = 0;
        base_stats[StatType::RESIST] = 0;
        base_stats[StatType::ACCURACY] = 0;
        base_stats[StatType::ARMOR_PEN] = 0;
        base_stats[StatType::MAGIC_PEN] = 0;
        // Attributes
        attributes[AttributeType::Strength] = 10;
        attributes[AttributeType::Agility] = 10;
        attributes[AttributeType::Intelligence] = 10;
        attributes[AttributeType::Charisma] = 10;
        attributes[AttributeType::Endurance] = 10;
        attributes[AttributeType::Wisdom] = 10;
        attributes[AttributeType::Perception] = 10;
}

void Creature::apply_buff(const Buff& buff) {
    buffs.push_back(buff);
    recalculate_stats();
}

void Creature::apply_debuff(const Buff& debuff) {
    debuffs.push_back(debuff);
    recalculate_stats();
}


void Creature::equip(const Equipment& item) {
    equipment.push_back(item);
    // Assign to armor/shield slot if appropriate
    if (item.type == EquipmentType::Armor) armor = &equipment.back();
    if (item.type == EquipmentType::Shield) shield = &equipment.back();
    recalculate_stats();
}


void Creature::unequip(const Equipment& item) {
    auto it = std::find_if(equipment.begin(), equipment.end(), [&](const Equipment& eq) { return eq.name == item.name; });
    if (it != equipment.end()) {
        if (armor == &(*it)) armor = nullptr;
        if (shield == &(*it)) shield = nullptr;
        equipment.erase(it);
    }
    recalculate_stats();
}

void Creature::heal(int points) {
    derived_stats[StatType::HP] += points;
    // Optionally clamp to max HP
}

void Creature::use_healing_item(const Equipment& item) {
    if (item.type == EquipmentType::HealingItem && item.heal_points > 0) {
        heal(item.heal_points);
    }
}

void Creature::recalculate_stats() {
    // Start with base stats
        derived_stats = base_stats;
        // Apply equipment modifiers
        for (const auto& eq : equipment) {
            for (const auto& mod : eq.stat_modifiers) {
                derived_stats[mod.first] += mod.second;
            }
        }
    // Apply buffs
    for (const auto& buff : buffs) {
        switch (buff.type) {
            case BuffType::ATK_UP: derived_stats[StatType::ATK] += buff.value; break;
            case BuffType::DEF_UP: derived_stats[StatType::DEF] += buff.value; break;
            case BuffType::SPD_UP: derived_stats[StatType::SPD] += buff.value; break;
            case BuffType::HP_REGEN: derived_stats[StatType::HP] += buff.value; break;
            case BuffType::MP_REGEN: derived_stats[StatType::MP] += buff.value; break;
            case BuffType::CRIT_UP: derived_stats[StatType::CRIT] += buff.value; break;
            case BuffType::EVADE_UP: derived_stats[StatType::EVADE] += buff.value; break;
            case BuffType::RESIST_UP: derived_stats[StatType::RESIST] += buff.value; break;
            default: break;
        }
    }
    // Apply debuffs
    for (const auto& debuff : debuffs) {
        switch (debuff.type) {
            case BuffType::POISON: derived_stats[StatType::HP] -= debuff.value; break;
            case BuffType::STUN: derived_stats[StatType::SPD] -= debuff.value; break;
            case BuffType::SLOW: derived_stats[StatType::SPD] -= debuff.value; break;
            case BuffType::WEAKEN: derived_stats[StatType::ATK] -= debuff.value; break;
            case BuffType::BURN: derived_stats[StatType::HP] -= debuff.value; break;
            case BuffType::FREEZE: derived_stats[StatType::SPD] -= debuff.value; break;
            case BuffType::CURSE: derived_stats[StatType::LUCK] -= debuff.value; break;
            default: break;
        }
    }
    // Derived stats can be further calculated here (e.g., formulas)
}

Monster::Monster(std::string name, SubType subtype, Race race)
    : Creature(std::move(name), Type::Monster, subtype, race), ferocity(10) {}

Animal::Animal(std::string name, SubType subtype, Race race)
    : Creature(std::move(name), Type::Animal, subtype, race), tameness(10) {}

} // namespace pox::game

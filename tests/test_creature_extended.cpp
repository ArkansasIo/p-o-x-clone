#include "pox/game/creature_extended.hpp"
#include <cassert>
#include <vector>

int main() {
    using namespace pox::game;
    Creature hero("Hero", Creature::Type::Humanoid, Creature::SubType::None, Creature::Race::Human);
    hero.body_parts.push_back(BodyPart(BodyPartType::Head, "Head", 100, 10, 5, true));
    hero.body_parts.push_back(BodyPart(BodyPartType::Torso, "Torso", 200, 20, 0));
    hero.body_parts.push_back(BodyPart(BodyPartType::ArmL, "Left Arm", 80, 8, 10));
    hero.body_parts.push_back(BodyPart(BodyPartType::ArmR, "Right Arm", 80, 8, 10));
    hero.body_parts.push_back(BodyPart(BodyPartType::LegL, "Left Leg", 90, 9, 0));
    hero.body_parts.push_back(BodyPart(BodyPartType::LegR, "Right Leg", 90, 9, 0));
    hero.body_parts.push_back(BodyPart(BodyPartType::Wing, "Wing", 60, 6, 0));
    hero.body_parts.push_back(BodyPart(BodyPartType::Tail, "Tail", 70, 7, 2));
    hero.body_parts.push_back(BodyPart(BodyPartType::Horn, "Horn", 50, 5, 15));

    // Test stats
    assert(hero.body_parts.size() == 9);
    assert(hero.body_parts[0].isCritical);
    assert(hero.body_parts[1].hp == 200);
    assert(hero.body_parts[8].attack == 15);

    // Test buffs
    Buff atkBuff{BuffType::ATK_UP, 10, 5};
    hero.apply_buff(atkBuff);
    assert(hero.buffs.size() == 1);

    // Test equipment
    Equipment sword{EquipmentType::Weapon, "Sword", {{StatType::ATK, 20}}, {}};
    hero.equip(sword);
    assert(hero.equipment.size() == 1);
    hero.recalculate_stats();
    assert(hero.derived_stats[StatType::ATK] >= 30);

    // Test debuff
    Buff poisonDebuff{BuffType::POISON, 5, 3};
    hero.apply_debuff(poisonDebuff);
    assert(hero.debuffs.size() == 1);

    return 0;
}

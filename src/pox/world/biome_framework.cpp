// Biome, Zone, Counter, and Condition Framework Implementation
#include "biome_framework.hpp"

namespace pox::world {

// Example biome definitions
const std::vector<Biome> biome_list = {
    {BiomeType::Forest, "Enchanted Forest", "temperate", {"poison", "ambush"}, {"wood", "herbs"}, {"wolf", "sprite"}, {"poisoned"}},
    {BiomeType::Desert, "Sandy Desert", "extreme_heat", {"heat", "sandstorm"}, {"cactus", "quartz"}, {"scorpion", "sand_worm"}, {"heatstroke"}},
    {BiomeType::Tundra, "Ice Shelf", "cold", {"frost", "slippery"}, {"ice", "fur"}, {"polar_bear", "frost_spirit"}, {"frostbite"}},
    {BiomeType::Volcanic, "Lava Fields", "extreme_heat", {"lava", "toxic_ash"}, {"obsidian", "sulfur"}, {"fire_elemental", "lava_beast"}, {"burning", "toxic_lung"}},
    {BiomeType::Aquatic, "Coral Reef", "mild", {"swimming", "oxygen"}, {"coral", "pearl"}, {"shark", "eel"}, {"dehydration"}},
    {BiomeType::Mountain, "Alpine Peaks", "cold", {"altitude", "fall"}, {"ore", "crystal"}, {"griffin", "mountain_goat"}, {"fatigue"}}
};

// Example zone definitions
const std::vector<Zone> zone_list = {
    {ZoneType::Safe, "Town", {"PvP disabled", "fast travel enabled", "healing regen boost"}, {"market", "festival"}},
    {ZoneType::Adventure, "Wilderness", {"PvE combat", "standard loot", "dynamic events"}, {"quest", "resource_gathering"}},
    {ZoneType::Danger, "Corrupted Lands", {"high difficulty", "rare drops", "hazard debuffs"}, {"invasion", "curse_event"}},
    {ZoneType::PvP, "Arena", {"open PvP", "rank gains", "territory control"}, {"battle", "tournament"}},
    {ZoneType::Dungeon, "Raid Tower", {"party required", "boss mechanics", "loot lockouts"}, {"boss_fight", "trial"}}
};

// Example counter definitions
const std::vector<Counter> counter_list = {
    {CounterType::Temperature, 0, 100, "Heat/cold exposure"},
    {CounterType::Hydration, 100, 100, "Dehydration mechanics"},
    {CounterType::Oxygen, 100, 100, "Underwater & altitude"},
    {CounterType::Fatigue, 0, 100, "Stamina regeneration"},
    {CounterType::Radiation, 0, 100, "Sci-fi zones"},
    {CounterType::Toxicity, 0, 100, "Poison gas areas"},
    {CounterType::Sanity, 100, 100, "Horror/dark zones"},
    {CounterType::Hunger, 100, 100, "Survival gameplay"},
    {CounterType::Pressure, 0, 100, "Deep ocean"},
    {CounterType::MagicSaturation, 0, 100, "Magic exposure"},
    {CounterType::Corruption, 0, 100, "Corrupted lands"}
};

// Example condition definitions
const std::vector<Condition> condition_list = {
    {ConditionType::Hypothermia, "Hypothermia", "Severe cold, HP loss", 60},
    {ConditionType::Frostbite, "Frostbite", "Cold, movement penalty", 30},
    {ConditionType::Heatstroke, "Heatstroke", "Heat, stamina drain", 45},
    {ConditionType::Dehydration, "Dehydration", "Water loss, HP drain", 40},
    {ConditionType::Poisoned, "Poisoned", "Poison, HP loss", 50},
    {ConditionType::Diseased, "Diseased", "Disease, stat reduction", 90},
    {ConditionType::RadiationSickness, "Radiation Sickness", "Radiation, HP loss", 80},
    {ConditionType::ToxicLung, "Toxic Lung", "Toxic air, stamina loss", 70},
    {ConditionType::Fear, "Fear", "Mental, accuracy penalty", 20},
    {ConditionType::Madness, "Madness", "Mental, random actions", 100},
    {ConditionType::Confusion, "Confusion", "Mental, control loss", 25},
    {ConditionType::Hallucination, "Hallucination", "Mental, visual distortion", 15},
    {ConditionType::Cursed, "Cursed", "Magic, stat reduction", 60},
    {ConditionType::ManaBurn, "Mana Burn", "Magic, MP loss", 35},
    {ConditionType::SoulDrain, "Soul Drain", "Magic, HP/MP loss", 50},
    {ConditionType::TemporalDistortion, "Temporal Distortion", "Magic, time effects", 10},
    {ConditionType::Burning, "Burning", "Fire, HP loss", 20},
    {ConditionType::CrushingDepth, "Crushing Depth", "Pressure, instant KO", 5}
};

// Example biome-counter-condition interactions
const std::vector<BiomeCounterCondition> interaction_list = {
    {BiomeCounterCondition{BiomeType::Desert, CounterType::Temperature, ConditionType::Heatstroke}},
    {BiomeCounterCondition{BiomeType::Tundra, CounterType::Temperature, ConditionType::Frostbite}},
    {BiomeCounterCondition{BiomeType::Swamp, CounterType::Toxicity, ConditionType::Poisoned}},
    {BiomeCounterCondition{BiomeType::Volcanic, CounterType::Temperature, ConditionType::Burning}},
    {BiomeCounterCondition{BiomeType::Aquatic, CounterType::Oxygen, ConditionType::Dehydration}},
    {BiomeCounterCondition{BiomeType::Mountain, CounterType::Fatigue, ConditionType::Hypothermia}},
    {BiomeCounterCondition{BiomeType::Corrupted, CounterType::Corruption, ConditionType::Madness}}
};

} // namespace pox::world

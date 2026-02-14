// Biome, Zone, Counter, and Condition Framework
#pragma once
#include <string>
#include <vector>
#include <map>

namespace pox::world {
// Extern declarations for global lists
extern const std::vector<Biome> biome_list;
extern const std::vector<Zone> zone_list;
extern const std::vector<Counter> counter_list;
extern const std::vector<Condition> condition_list;
extern const std::vector<BiomeCounterCondition> interaction_list;

// Biome types
enum class BiomeType {
    Forest, Desert, Tundra, Volcanic, Aquatic, Mountain, Swamp, Enchanted, Haunted, Glass, Coral, Abyssal, Crystal, Corrupted
};

struct Biome {
    BiomeType type;
    std::string name;
    std::string temperature;
    std::vector<std::string> hazards;
    std::vector<std::string> resources;
    std::vector<std::string> enemy_types;
    std::vector<std::string> status_effects;
};

// Zone types
enum class ZoneType {
    Safe, Adventure, Danger, PvP, Dungeon
};

struct Zone {
    ZoneType type;
    std::string name;
    std::vector<std::string> rules;
    std::vector<std::string> events;
};

// Survival counters
enum class CounterType {
    Temperature, Hydration, Oxygen, Fatigue, Radiation, Toxicity, Sanity, Hunger, Pressure, MagicSaturation, Corruption
};

struct Counter {
    CounterType type;
    int value;
    int max;
    std::string description;
};

// Condition states
enum class ConditionType {
    Hypothermia, Frostbite, Heatstroke, Dehydration, Poisoned, Diseased, RadiationSickness, ToxicLung, Fear, Madness, Confusion, Hallucination, Cursed, ManaBurn, SoulDrain, TemporalDistortion, Burning, CrushingDepth
};

struct Condition {
    ConditionType type;
    std::string name;
    std::string effect;
    int duration;
};

// Example biome interaction
struct BiomeCounterCondition {
    BiomeType biome;
    CounterType counter;
    ConditionType condition;
};

} // namespace pox::world

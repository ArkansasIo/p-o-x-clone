// Biome, Zone, Counter, and Condition Framework Header
#pragma once
#include <string>
#include <vector>

namespace pox {
namespace world {

enum class BiomeType {
    Forest, Desert, Tundra, Volcanic, Aquatic, Mountain, Swamp, Corrupted
};

enum class ZoneType {
    Safe, Adventure, Danger, PvP, Dungeon
};

enum class CounterType {
    Temperature, Hydration, Oxygen, Fatigue, Radiation, Toxicity, Sanity, Hunger, Pressure, MagicSaturation, Corruption
};

enum class ConditionType {
    Hypothermia, Frostbite, Heatstroke, Dehydration, Poisoned, Diseased, RadiationSickness, ToxicLung, Fear, Madness, Confusion, Hallucination, Cursed, ManaBurn, SoulDrain, TemporalDistortion, Burning, CrushingDepth
};

struct Biome {
    BiomeType type;
    std::string name;
    std::string climate;
    std::vector<std::string> hazards;
    std::vector<std::string> resources;
    std::vector<std::string> creatures;
    std::vector<std::string> conditions;
};

struct Zone {
    ZoneType type;
    std::string name;
    std::vector<std::string> features;
    std::vector<std::string> events;
};

struct Counter {
    CounterType type;
    int min;
    int max;
    std::string description;
};

struct Condition {
    ConditionType type;
    std::string name;
    std::string effect;
    int severity;
};

struct BiomeCounterCondition {
    BiomeType biome;
    CounterType counter;
    ConditionType condition;
};

extern const std::vector<Biome> biome_list;
extern const std::vector<Zone> zone_list;
extern const std::vector<Counter> counter_list;
extern const std::vector<Condition> condition_list;
extern const std::vector<BiomeCounterCondition> interaction_list;

} // namespace world
} // namespace pox

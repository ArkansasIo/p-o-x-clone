#include "pox/world/biome_framework.hpp"
#include <cassert>

int main() {
    using namespace pox::world;
    extern const std::vector<Biome> biome_list;
    extern const std::vector<Zone> zone_list;
    extern const std::vector<Counter> counter_list;
    extern const std::vector<Condition> condition_list;
    extern const std::vector<BiomeCounterCondition> interaction_list;
    assert(biome_list.size() >= 6);
    assert(zone_list.size() >= 5);
    assert(counter_list.size() >= 11);
    assert(condition_list.size() >= 18);
    assert(interaction_list.size() >= 7);
    assert(biome_list[0].type == BiomeType::Forest);
    assert(zone_list[0].type == ZoneType::Safe);
    assert(counter_list[0].type == CounterType::Temperature);
    assert(condition_list[0].type == ConditionType::Hypothermia);
    assert(interaction_list[0].biome == BiomeType::Desert);
    return 0;
}

// Continents and countries header
#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Country {
    std::string name;
    std::string description;
    int continent_idx;
};

struct Continent {
    std::string name;
    std::string description;
    std::vector<int> country_indices;
};

class WorldMap {
public:
    void initialize();
    std::vector<Country> countries;
    std::vector<Continent> continents;
};

} // namespace game
} // namespace pox

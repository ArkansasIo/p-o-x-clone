#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Country {
    std::string name;
    std::string description;
    int continent_index;
};

struct Continent {
    std::string name;
    std::string description;
    std::vector<int> country_indices; // Indices of countries belonging to this continent
};

struct WorldMap {
    std::vector<Country> countries;
    std::vector<Continent> continents;
    void initialize();
};

} // namespace game
} // namespace pox

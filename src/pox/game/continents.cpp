#include "continents.hpp"
#include <sstream>

namespace pox {
namespace game {

void WorldMap::initialize() {
    // Create 72 countries
    for (int i = 1; i <= 72; ++i) {
        std::ostringstream name;
        name << "Country " << i;
        std::ostringstream desc;
        desc << "Description for Country " << i;
        int continent_idx = (i-1) / 8; // 8 countries per continent
        countries.push_back({name.str(), desc.str(), continent_idx});
    }
    // Create 9 continents
    for (int c = 1; c <= 9; ++c) {
        std::ostringstream name;
        name << "Continent " << c;
        std::ostringstream desc;
        desc << "Description for Continent " << c;
        std::vector<int> country_indices;
        for (int i = (c-1)*8; i < c*8; ++i) {
            country_indices.push_back(i);
        }
        continents.push_back({name.str(), desc.str(), country_indices});
    }
}

} // namespace game
} // namespace pox

#include "kingdoms.hpp"
#include <sstream>

namespace pox {
namespace game {

void initialize_kingdoms(KingdomSystem& kingdomSys) {
    for (int k = 1; k <= 12; ++k) {
        std::ostringstream name;
        name << "Kingdom " << k;
        std::ostringstream desc;
        desc << "Description for Kingdom " << k;
        std::vector<int> zone_indices;
        for (int z = (k-1)*6; z < k*6; ++z) {
            zone_indices.push_back(z);
        }
        kingdomSys.add_kingdom({name.str(), desc.str(), zone_indices});
    }
}

void KingdomSystem::add_kingdom(const Kingdom& kingdom) {
    kingdoms.push_back(kingdom);
}

const Kingdom& KingdomSystem::get_kingdom(int idx) const {
    return kingdoms[idx];
}

} // namespace game
} // namespace pox

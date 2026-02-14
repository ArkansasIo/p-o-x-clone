#include "zones.hpp"
#include <sstream>

namespace pox {
namespace game {

ZoneSystem::ZoneSystem() : current_zone(0) {
    // Initialize 72 world zones
    for (int i = 1; i <= 72; ++i) {
        std::ostringstream name;
        name << "Zone " << i;
        std::ostringstream desc;
        desc << "Description for Zone " << i;
        zones.push_back({name.str(), desc.str(), i == 1}); // Only first zone unlocked
    }
}

void ZoneSystem::add_zone(const Zone& zone) {
    zones.push_back(zone);
}

void ZoneSystem::unlock_zone(int idx) {
    if (idx >= 0 && idx < static_cast<int>(zones.size())) {
        zones[idx].unlocked = true;
    }
}

void ZoneSystem::set_zone(int idx) {
    if (idx >= 0 && idx < static_cast<int>(zones.size()) && zones[idx].unlocked) {
        current_zone = idx;
    }
}

const Zone& ZoneSystem::get_current_zone() const {
    return zones[current_zone];
}

} // namespace game
} // namespace pox

#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Zone {
    std::string name;
    std::string description;
    bool unlocked;
};

struct ZoneSystem {
    std::vector<Zone> zones;
    int current_zone;

    ZoneSystem();
    void add_zone(const Zone& zone);
    void unlock_zone(int idx);
    void set_zone(int idx);
    const Zone& get_current_zone() const;
};

} // namespace game
} // namespace pox

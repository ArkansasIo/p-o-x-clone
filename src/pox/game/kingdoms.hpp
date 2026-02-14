// Kingdoms system header
#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Kingdom {
    std::string name;
    std::string description;
    std::vector<int> zone_indices;
};

class KingdomSystem {
public:
    void add_kingdom(const Kingdom& kingdom);
    const Kingdom& get_kingdom(int idx) const;
    std::vector<Kingdom> kingdoms;
};

void initialize_kingdoms(KingdomSystem& kingdomSys);

} // namespace game
} // namespace pox

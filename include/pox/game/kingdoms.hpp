#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Kingdom {
    std::string name;
    std::string description;
    std::vector<int> zone_indices; // Indices of zones belonging to this kingdom
};

struct KingdomSystem {
    std::vector<Kingdom> kingdoms;
    void add_kingdom(const Kingdom& kingdom);
    const Kingdom& get_kingdom(int idx) const;
};

} // namespace game
} // namespace pox

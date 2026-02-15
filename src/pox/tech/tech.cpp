#include "tech.hpp"
#include <algorithm>

void PlayerTechTree::unlockTech(uint16_t id) {
    auto it = std::find_if(techs.begin(), techs.end(), [id](const Tech& t) { return t.id == id; });
    if (it != techs.end()) {
        it->unlocked = true;
    }
}

bool PlayerTechTree::isUnlocked(uint16_t id) const {
    auto it = std::find_if(techs.begin(), techs.end(), [id](const Tech& t) { return t.id == id; });
    return it != techs.end() && it->unlocked;
}

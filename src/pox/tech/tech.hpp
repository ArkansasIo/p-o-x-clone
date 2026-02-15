#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct Tech {
    uint16_t id;
    std::string name;
    std::string description;
    std::vector<uint16_t> prerequisites;
    bool unlocked = false;
};

struct PlayerTechTree {
    std::vector<Tech> techs;
    void unlockTech(uint16_t id);
    bool isUnlocked(uint16_t id) const;
};

// Resource and tech tree system
#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace pox::resource {

struct Resource {
    uint8_t id;
    std::string name;
    int quantity;
};

struct PlayerResources {
    std::vector<Resource> resources;
    void addResource(uint8_t id, int amount);
    bool spendResource(uint8_t id, int amount);
};

struct Tech {
    uint16_t id;
    std::string name;
    std::string description;
    std::vector<uint16_t> prerequisites;
    bool unlocked;
};

struct PlayerTechTree {
    std::vector<Tech> techs;
    void unlockTech(uint16_t id);
    bool isUnlocked(uint16_t id) const;
};

} // namespace pox::resource

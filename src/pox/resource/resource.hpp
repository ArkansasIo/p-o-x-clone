#pragma once
#include <vector>
#include <string>
#include <cstdint>

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

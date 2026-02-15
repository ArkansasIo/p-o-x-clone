// Room and universe system
#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <random>

namespace pox::universe {

struct PlayerInfo {
    uint8_t id;
    std::string name;
};

struct Room {
    uint32_t roomID;
    std::string name;
    std::vector<PlayerInfo> players;
    uint32_t planetSeed;
};

struct Universe {
    uint64_t universeSeed;
    std::vector<uint64_t> planetSeeds;
};

std::vector<uint64_t> generatePlanets(uint64_t universeSeed, int numPlanets);
Room joinRoom(uint64_t planetSeed);

} // namespace pox::universe

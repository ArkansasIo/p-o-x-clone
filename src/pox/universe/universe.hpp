#pragma once
#include <vector>
#include <string>
#include <random>
#include <cstdint>

struct PlayerInfo {
    uint8_t id;
    std::string name;
    // Add player state, position, etc.
};

struct Room {
    uint32_t roomID;
    std::string name;
    std::vector<PlayerInfo> players; // up to 32
    uint64_t planetSeed; // For open world context
    // Add room/game state
};

struct Universe {
    uint64_t universeSeed;
    std::vector<uint64_t> planetSeeds;
};

std::vector<uint64_t> generatePlanets(uint64_t universeSeed, int numPlanets);
Room joinRoom(uint64_t planetSeed, const PlayerInfo& player);

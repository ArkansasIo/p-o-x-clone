#include "universe.hpp"
#include <algorithm>

std::vector<uint64_t> generatePlanets(uint64_t universeSeed, int numPlanets) {
    std::vector<uint64_t> seeds;
    std::mt19937_64 rng(universeSeed);
    for (int i = 0; i < numPlanets; ++i) {
        seeds.push_back(rng());
    }
    return seeds;
}

// Simple in-memory room registry for demonstration
static std::vector<Room> g_rooms;

Room joinRoom(uint64_t planetSeed, const PlayerInfo& player) {
    // Find or create room for this planet
    auto it = std::find_if(g_rooms.begin(), g_rooms.end(), [planetSeed](const Room& r) {
        return r.planetSeed == planetSeed;
    });
    if (it == g_rooms.end()) {
        Room newRoom;
        newRoom.roomID = static_cast<uint32_t>(planetSeed & 0xFFFFFFFF);
        newRoom.name = "PlanetRoom_" + std::to_string(planetSeed);
        newRoom.planetSeed = planetSeed;
        newRoom.players.push_back(player);
        g_rooms.push_back(newRoom);
        return newRoom;
    } else {
        if (it->players.size() < 32) {
            it->players.push_back(player);
        }
        return *it;
    }
}

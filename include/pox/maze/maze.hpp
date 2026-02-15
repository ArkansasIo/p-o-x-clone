// Maze system for procedural generation and exploration
#pragma once
#include <vector>
#include <cstdint>
#include <random>
#include <string>

namespace pox::maze {

struct MazeCell {
    bool wall_north = true;
    bool wall_south = true;
    bool wall_east = true;
    bool wall_west = true;
    bool visited = false;
    // Items, enemies, loot, etc.
};

enum class MazeType {
    Standard,
    Trial,
    Raid,
    Dungeon,
    Tower,
    World,
    Event
};

struct MazeLevel {
    uint32_t levelIndex;
    uint64_t seed;
    int width, height;
    MazeType type = MazeType::Standard;
    std::string theme; // e.g. "POX Lab", "Infection Tower", "Bio-Dungeon"
    std::vector<std::vector<MazeCell>> grid;
    // Add more RPG/MMO features as needed (bosses, loot tables, objectives, etc.)
};

MazeLevel generateMaze(uint32_t levelIndex, int width, int height, uint64_t baseSeed, MazeType type = MazeType::Standard, const std::string& theme = "");
std::string describeMaze(const MazeLevel& maze);

} // namespace pox::maze

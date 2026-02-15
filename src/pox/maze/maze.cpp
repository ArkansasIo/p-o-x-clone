// Maze system implementation (procedural generation)
#include "pox/maze/maze.hpp"
#include <sstream>

namespace pox::maze {

MazeLevel generateMaze(uint32_t levelIndex, int width, int height, uint64_t baseSeed, MazeType type, const std::string& theme) {
    MazeLevel maze;
    maze.levelIndex = levelIndex;
    maze.seed = baseSeed ^ (levelIndex * 0x9e3779b97f4a7c15);
    maze.width = width;
    maze.height = height;
    maze.type = type;
    maze.theme = theme;
    maze.grid.resize(height, std::vector<MazeCell>(width));
    std::mt19937_64 rng(maze.seed);
    // Simple DFS maze generation
    std::vector<std::pair<int, int>> stack;
    stack.emplace_back(0, 0);
    maze.grid[0][0].visited = true;
    while (!stack.empty()) {
        auto [x, y] = stack.back();
        std::vector<std::pair<int, int>> neighbors;
        if (y > 0 && !maze.grid[y-1][x].visited) neighbors.emplace_back(x, y-1);
        if (y < height-1 && !maze.grid[y+1][x].visited) neighbors.emplace_back(x, y+1);
        if (x > 0 && !maze.grid[y][x-1].visited) neighbors.emplace_back(x-1, y);
        if (x < width-1 && !maze.grid[y][x+1].visited) neighbors.emplace_back(x+1, y);
        if (!neighbors.empty()) {
            auto [nx, ny] = neighbors[rng() % neighbors.size()];
            // Remove wall between (x,y) and (nx,ny)
            if (nx == x && ny == y-1) { maze.grid[y][x].wall_north = false; maze.grid[ny][nx].wall_south = false; }
            if (nx == x && ny == y+1) { maze.grid[y][x].wall_south = false; maze.grid[ny][nx].wall_north = false; }
            if (nx == x-1 && ny == y) { maze.grid[y][x].wall_west = false; maze.grid[ny][nx].wall_east = false; }
            if (nx == x+1 && ny == y) { maze.grid[y][x].wall_east = false; maze.grid[ny][nx].wall_west = false; }
            maze.grid[ny][nx].visited = true;
            stack.emplace_back(nx, ny);
        } else {
            stack.pop_back();
        }
    }
    // Add POX RPG/MMO features based on type
    // Example: boss for Raid, loot for Dungeon, tower floors, world events, etc.
    // (Extend here as needed)
    return maze;
}

std::string describeMaze(const MazeLevel& maze) {
    std::ostringstream oss;
    oss << "Maze Level " << maze.levelIndex << " (" << maze.width << "x" << maze.height << ")\n";
    for (int y = 0; y < maze.height; ++y) {
        for (int x = 0; x < maze.width; ++x) {
            oss << (maze.grid[y][x].wall_north ? "+---" : "+   ");
        }
        oss << "+\n";
        for (int x = 0; x < maze.width; ++x) {
            oss << (maze.grid[y][x].wall_west ? "|   " : "    ");
        }
        oss << "|\n";
    }
    for (int x = 0; x < maze.width; ++x) oss << "+---";
    oss << "+\n";
    return oss.str();
}

} // namespace pox::maze

#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Dungeon {
    std::string name;
    std::string description;
    int level_required;
};

struct Trial {
    std::string name;
    std::string description;
    int level_required;
};

struct Raid {
    std::string name;
    std::string description;
    int level_required;
    int max_players;
};

struct LevelSystem {
    int current_level;
    static constexpr int max_level = 150;
    void level_up();
    void set_level(int lvl);
};

struct RPGSystems {
    std::vector<Dungeon> dungeons;
    std::vector<Trial> trials;
    std::vector<Raid> raids;
    LevelSystem level_system;
    void initialize();
};

} // namespace game
} // namespace pox

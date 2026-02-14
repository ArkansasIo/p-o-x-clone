// RPG systems header
#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct Dungeon {
    std::string name;
    std::string description;
    int id;
};

struct Trial {
    std::string name;
    std::string description;
    int id;
};

struct Raid {
    std::string name;
    std::string description;
    int id;
    int min_level;
};

class LevelSystem {
public:
    void level_up();
    void set_level(int lvl);
    int current_level = 1;
    int max_level = 99;
};

class RPGSystems {
public:
    void initialize();
    std::vector<Dungeon> dungeons;
    std::vector<Trial> trials;
    std::vector<Raid> raids;
    LevelSystem level_system;
};

} // namespace game
} // namespace pox

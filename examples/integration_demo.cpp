// Example integration of Maze, Database, RPG, and Universe systems
#include "pox/maze/maze.hpp"
#include "pox/db/database.hpp"
#include "pox/rpg/rpg.hpp"
#include "pox/universe/universe.hpp"
#include <iostream>

int main() {
    // 1. Generate a dungeon maze
    auto maze = pox::maze::generateMaze(1, 10, 10, 0xCAFEBABE, pox::maze::MazeType::Dungeon, "POX Dungeon");
    std::cout << pox::maze::describeMaze(maze) << std::endl;

    // 2. Create a game database and add a creature
    pox::db::Database db;
    db.createTable("creatures", {
        {"id", "int"},
        {"num", "int"},
        {"name", "string"},
        {"type", "string"},
        {"hp", "int"},
        {"attack", "int"}
    });
    db.insert("creatures", {{
        {"id", 1},
        {"num", 101},
        {"name", "Infector"},
        {"type", "virus"},
        {"hp", 100},
        {"attack", 20}
    }});
    auto results = db.select("creatures", "name=Infector");
    std::cout << "Database: Found " << results.size() << " creature(s) named Infector." << std::endl;

    // 3. Create and level up an RPG character
    auto character = pox::rpg::createCharacter("Player1");
    pox::rpg::gainExperience(character, 1000);
    std::cout << "Character: " << character.name << ", Level: " << character.level << std::endl;

    // 4. Generate universe and join a room
    auto planetSeeds = pox::universe::generatePlanets(0x12345678, 5);
    auto room = pox::universe::joinRoom(planetSeeds[0]);
    std::cout << "Joined room for planet seed: " << room.planetSeed << std::endl;

    return 0;
}

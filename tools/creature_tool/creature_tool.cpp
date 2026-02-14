// Creature tool implementation
#include "creature_tool.hpp"
#include <fstream>
#include <iostream>

namespace pox_tool {

CreatureTool::CreatureTool() {}

void CreatureTool::load(const std::string& filename) {
    // Placeholder: load creatures from file
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    // ...parse creatures...
}

void CreatureTool::save(const std::string& filename) {
    // Placeholder: save creatures to file
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    // ...write creatures...
}

void CreatureTool::addCreature(const pox::game::Creature& creature) {
    creatures.push_back(creature);
}

} // namespace pox_tool

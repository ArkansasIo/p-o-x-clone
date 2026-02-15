// pox1_loader.cpp
#include "pox1_loader.hpp"
#include <fstream>
#include <sstream>
#include <vector>

std::vector<SpriteIndexEntry> load_pox1_index(const std::string& path) {
    std::vector<SpriteIndexEntry> entries;
    std::ifstream f(path);
    std::string line;
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        SpriteIndexEntry e;
        iss >> e.id >> e.offset >> e.size >> e.bpp >> e.width >> e.height >> e.frames;
        entries.push_back(e);
    }
    return entries;
}

#include "pox/game/wad_resources.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace pox::game {

bool WADResources::load_json(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    nlohmann::json j;
    f >> j;
    sprites = j["sprites"].get<std::vector<std::string>>();
    name_chars = j["name_chars"].get<std::vector<std::string>>();
    return true;
}

} // namespace pox::game

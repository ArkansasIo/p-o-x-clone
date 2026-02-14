#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace pox::game {

struct WADResources {
    std::vector<std::string> sprites;
    std::vector<std::string> name_chars;
    bool load_json(const std::string& path);
};

} // namespace pox::game

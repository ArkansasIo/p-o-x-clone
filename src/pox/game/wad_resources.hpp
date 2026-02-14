// WAD resources header
#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

class WADResources {
public:
    bool load_json(const std::string& path);
    std::vector<std::string> sprites;
    std::vector<std::string> name_chars;
};

} // namespace game
} // namespace pox

// Settings system header
#pragma once
#include <string>
#include <unordered_map>

namespace pox {
namespace game {

struct Setting {
    std::string key;
    std::string value;
};

class SettingsSystem {
public:
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key) const;
private:
    std::unordered_map<std::string, Setting> settings;
};

} // namespace game
} // namespace pox

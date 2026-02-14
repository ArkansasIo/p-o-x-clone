#include "settings.hpp"

namespace pox {
namespace game {

void SettingsSystem::set(const std::string& key, const std::string& value) {
    settings[key] = Setting{key, value};
}

std::string SettingsSystem::get(const std::string& key) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        return it->second.value;
    }
    return "";
}

} // namespace game
} // namespace pox

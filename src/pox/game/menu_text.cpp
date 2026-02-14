#include "menu_text.hpp"

namespace pox {
namespace game {

MenuTextSystem::MenuTextSystem() : current_zone(0), current_option(0) {}

void MenuTextSystem::add_zone(const MenuZone& zone) {
    zones.push_back(zone);
}

void MenuTextSystem::set_zone(int idx) {
    if (idx >= 0 && idx < static_cast<int>(zones.size())) {
        current_zone = idx;
        current_option = 0;
    }
}

void MenuTextSystem::set_option(int idx) {
    if (current_zone >= 0 && current_zone < static_cast<int>(zones.size())) {
        const auto& zone = zones[current_zone];
        if (idx >= 0 && idx < static_cast<int>(zone.options.size())) {
            current_option = idx;
        }
    }
}

const MenuZone& MenuTextSystem::get_current_zone() const {
    return zones[current_zone];
}

const MenuOption& MenuTextSystem::get_current_option() const {
    return zones[current_zone].options[current_option];
}

} // namespace game
} // namespace pox

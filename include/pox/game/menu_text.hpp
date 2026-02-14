#pragma once
#include <string>
#include <vector>

namespace pox {
namespace game {

struct MenuOption {
    std::string label;
    bool enabled;
};

struct MenuZone {
    std::string title;
    std::vector<MenuOption> options;
};

struct MenuTextSystem {
    std::vector<MenuZone> zones;
    int current_zone;
    int current_option;

    MenuTextSystem();
    void add_zone(const MenuZone& zone);
    void set_zone(int idx);
    void set_option(int idx);
    const MenuZone& get_current_zone() const;
    const MenuOption& get_current_option() const;
};

} // namespace game
} // namespace pox

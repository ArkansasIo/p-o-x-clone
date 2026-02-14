// Inventory system for creatures and player
#pragma once
#include <vector>
#include <string>
#include "creature_extended.hpp"

namespace pox {
namespace game {

class Inventory {
public:
    void add_item(const Equipment& item);
    bool remove_item(const std::string& name);
    Equipment* get_item(const std::string& name);
    const std::vector<Equipment>& items() const;
private:
    std::vector<Equipment> items_;
};

} // namespace game
} // namespace pox

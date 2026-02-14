#include "inventory.hpp"

namespace pox {
namespace game {

void Inventory::add_item(const Equipment& item) {
    items_.push_back(item);
}

bool Inventory::remove_item(const std::string& name) {
    auto it = std::find_if(items_.begin(), items_.end(), [&](const Equipment& eq) { return eq.name == name; });
    if (it != items_.end()) {
        items_.erase(it);
        return true;
    }
    return false;
}

Equipment* Inventory::get_item(const std::string& name) {
    auto it = std::find_if(items_.begin(), items_.end(), [&](const Equipment& eq) { return eq.name == name; });
    if (it != items_.end()) {
        return &(*it);
    }
    return nullptr;
}

const std::vector<Equipment>& Inventory::items() const {
    return items_;
}

} // namespace game
} // namespace pox

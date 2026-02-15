#include "inventory.hpp"
#include <algorithm>

void Inventory::addItem(uint32_t id, const std::string& name, int quantity) {
    auto it = std::find_if(items.begin(), items.end(), [id](const Item& item) { return item.id == id; });
    if (it != items.end()) {
        it->quantity += quantity;
    } else {
        items.push_back({id, name, quantity});
    }
}

bool Inventory::removeItem(uint32_t id, int quantity) {
    auto it = std::find_if(items.begin(), items.end(), [id](const Item& item) { return item.id == id; });
    if (it != items.end() && it->quantity >= quantity) {
        it->quantity -= quantity;
        if (it->quantity == 0) items.erase(it);
        return true;
    }
    return false;
}

bool Inventory::hasItem(uint32_t id, int quantity) const {
    auto it = std::find_if(items.begin(), items.end(), [id](const Item& item) { return item.id == id; });
    return it != items.end() && it->quantity >= quantity;
}

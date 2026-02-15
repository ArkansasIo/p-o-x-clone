#include "trade.hpp"

bool tradeItems(Character& a, Character& b, uint32_t itemId, int amount) {
    // For demonstration, assume Character has Inventory member named 'inventory'
    if (a.inventory.hasItem(itemId, amount)) {
        a.inventory.removeItem(itemId, amount);
        b.inventory.addItem(itemId, "Item" + std::to_string(itemId), amount);
        return true;
    }
    return false;
}

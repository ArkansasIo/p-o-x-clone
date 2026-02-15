#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct Item {
    uint32_t id;
    std::string name;
    int quantity;
    // Add item stats, type, etc.
};

struct Inventory {
    std::vector<Item> items;
    void addItem(uint32_t id, const std::string& name, int quantity = 1);
    bool removeItem(uint32_t id, int quantity = 1);
    bool hasItem(uint32_t id, int quantity = 1) const;
};

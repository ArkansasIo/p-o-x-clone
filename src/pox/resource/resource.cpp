#include "resource.hpp"
#include <algorithm>

void PlayerResources::addResource(uint8_t id, int amount) {
    auto it = std::find_if(resources.begin(), resources.end(), [id](const Resource& r) { return r.id == id; });
    if (it != resources.end()) {
        it->quantity += amount;
    } else {
        resources.push_back({id, "Resource" + std::to_string(id), amount});
    }
}

bool PlayerResources::spendResource(uint8_t id, int amount) {
    auto it = std::find_if(resources.begin(), resources.end(), [id](const Resource& r) { return r.id == id; });
    if (it != resources.end() && it->quantity >= amount) {
        it->quantity -= amount;
        return true;
    }
    return false;
}

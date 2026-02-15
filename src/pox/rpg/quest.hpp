#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Quest {
    uint32_t id;
    std::string name;
    std::string description;
    bool completed = false;
    // Objectives, rewards, etc.
};

void startQuest(Character& c, uint32_t questId);
void completeQuest(Character& c, uint32_t questId);

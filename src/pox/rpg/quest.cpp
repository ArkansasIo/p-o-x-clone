#include "quest.hpp"
#include "character.hpp"
#include <vector>

// For demonstration, quests are not stored per character. In a real system, add quest tracking to Character.
static std::vector<Quest> g_quests;

void startQuest(Character& c, uint32_t questId) {
    // Add quest to global list (stub)
    g_quests.push_back({questId, "Quest" + std::to_string(questId), "Description", false});
}

void completeQuest(Character& c, uint32_t questId) {
    for (auto& q : g_quests) {
        if (q.id == questId) q.completed = true;
    }
}

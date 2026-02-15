#include "chat.hpp"
#include <vector>

static std::vector<Message> g_messages;

void sendMessage(uint32_t fromId, uint32_t toId, const std::string& msg) {
    g_messages.push_back({fromId, toId, msg});
}

std::vector<Message> getMessages(uint32_t playerId) {
    std::vector<Message> inbox;
    for (const auto& m : g_messages) {
        if (m.toId == playerId) inbox.push_back(m);
    }
    return inbox;
}

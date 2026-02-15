#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Message {
    uint32_t fromId;
    uint32_t toId;
    std::string text;
};

void sendMessage(uint32_t fromId, uint32_t toId, const std::string& msg);
std::vector<Message> getMessages(uint32_t playerId);

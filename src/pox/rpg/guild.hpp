#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct Guild {
    uint32_t id;
    std::string name;
    std::vector<uint32_t> memberIds;
};

void joinGuild(uint32_t playerId, Guild& guild);
void leaveGuild(uint32_t playerId, Guild& guild);

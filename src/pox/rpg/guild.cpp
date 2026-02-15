#include "guild.hpp"
#include <algorithm>

void joinGuild(uint32_t playerId, Guild& guild) {
    if (std::find(guild.memberIds.begin(), guild.memberIds.end(), playerId) == guild.memberIds.end()) {
        guild.memberIds.push_back(playerId);
    }
}

void leaveGuild(uint32_t playerId, Guild& guild) {
    auto it = std::remove(guild.memberIds.begin(), guild.memberIds.end(), playerId);
    if (it != guild.memberIds.end()) {
        guild.memberIds.erase(it, guild.memberIds.end());
    }
}

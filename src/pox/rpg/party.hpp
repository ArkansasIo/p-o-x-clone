#pragma once
#include <vector>
#include "character.hpp"

struct Party {
    std::vector<Character> members;
};

void joinParty(Character& c, Party& party);

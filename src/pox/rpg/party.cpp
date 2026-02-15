#include "party.hpp"
#include <algorithm>

void joinParty(Character& c, Party& party) {
    if (std::find_if(party.members.begin(), party.members.end(), [&](const Character& m) { return m.id == c.id; }) == party.members.end()) {
        party.members.push_back(c);
    }
}

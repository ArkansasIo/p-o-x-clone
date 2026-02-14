#include "pox/game/creature_db.hpp"
#include <cassert>
#include <array>

int main() {
    pox::game::CreatureDB db(2);
    std::array<uint8_t, 40> sram{};
    db.load_from_sram(sram.data(), sram.size());
    db.slot(0).head_id = 0x42;
    db.save_to_sram(sram.data(), sram.size());
    pox::game::CreatureDB db2(2);
    db2.load_from_sram(sram.data(), sram.size());
    assert(db2.slot(0).head_id == 0x42);
    return 0;
}

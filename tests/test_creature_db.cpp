#include "pox/game/creature_db.hpp"
#include <cassert>
#include <cstdio>
#include <array>

int main() {
    pox::game::CreatureDB db(2);
    std::array<uint8_t, 72> sram{}; // 2 records * 36 bytes each
    db.load_from_sram(sram.data(), sram.size());
    db.slot(0).head_id = 0x42;
    printf("db.slot(0).head_id before save = %u\n", db.slot(0).head_id);
    db.save_to_sram(sram.data(), sram.size());
    printf("SRAM after save: ");
    for (size_t i = 0; i < sram.size(); ++i) printf("%02X ", sram[i]);
    printf("\n");
    fflush(stdout);
    pox::game::CreatureDB db2(2);
    db2.load_from_sram(sram.data(), sram.size());
    printf("SRAM before load: ");
    for (size_t i = 0; i < sram.size(); ++i) printf("%02X ", sram[i]);
    printf("\n");
    fflush(stdout);
    printf("db2.slot(0).head_id after load = %u\n", db2.slot(0).head_id);
    fflush(stdout);
    assert(db2.slot(0).head_id == 0x42);
    return 0;
}

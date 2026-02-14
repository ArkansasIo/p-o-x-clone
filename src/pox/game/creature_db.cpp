#include "pox/game/creature_db.hpp"
#include <cstring>

namespace pox::game {

CreatureDB::CreatureDB(size_t slots) : slots_(slots) {}


bool CreatureDB::load_from_sram(const uint8_t* sram, size_t len) {
    if (len < slots_.size() * record_size) return false;
    for (size_t i = 0; i < slots_.size(); ++i) {
        std::array<uint8_t, record_size> rec{};
        std::memcpy(rec.data(), sram + i * record_size, record_size);
        slots_[i] = CreatureRecord::deserialize(rec);
    }
    return true;
}


void CreatureDB::save_to_sram(uint8_t* sram, size_t len) const {
    if (len < slots_.size() * record_size) return;
    for (size_t i = 0; i < slots_.size(); ++i) {
        auto rec = slots_[i].serialize();
        std::memcpy(sram + i * record_size, rec.data(), record_size);
    }
}

CreatureRecord& CreatureDB::slot(size_t i) { return slots_[i]; }
const CreatureRecord& CreatureDB::slot(size_t i) const { return slots_[i]; }
size_t CreatureDB::slot_count() const { return slots_.size(); }

} // namespace pox::game

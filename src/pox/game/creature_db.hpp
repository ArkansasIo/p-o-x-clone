// Creature database header
#pragma once
#include <vector>
#include <array>
#include <cstdint>
#include "creature_record.hpp"

namespace pox {
namespace game {

class CreatureDB {
public:
    CreatureDB(size_t slots);
    bool load_from_sram(const uint8_t* sram, size_t len);
    void save_to_sram(uint8_t* sram, size_t len) const;
    CreatureRecord& slot(size_t i);
    const CreatureRecord& slot(size_t i) const;
    size_t slot_count() const;

private:
    std::vector<CreatureRecord> slots_;
    static constexpr size_t record_size = 36;
};

} // namespace game
} // namespace pox

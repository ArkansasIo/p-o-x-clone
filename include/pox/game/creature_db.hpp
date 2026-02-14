#pragma once
#include <cstdint>
#include <vector>
#include "creature_record.hpp"

namespace pox::game {

class CreatureDB {
public:
    CreatureDB(size_t slots = 8);
    bool load_from_sram(const uint8_t* sram, size_t len);
    void save_to_sram(uint8_t* sram, size_t len) const;
    CreatureRecord& slot(size_t i);
    const CreatureRecord& slot(size_t i) const;
    size_t slot_count() const;
private:
    std::vector<CreatureRecord> slots_;
};

} // namespace pox::game

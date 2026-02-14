#pragma once
#include <cstdint>
#include <array>
#include <string>

namespace pox::game {

struct CreatureRecord {
    uint8_t head_id, head_hp;
    uint8_t body_id, body_hp;
    uint8_t tail_id, tail_hp;
    std::array<uint8_t, 6> wad_indices;
    std::array<uint8_t, 6> name_indices;
    uint16_t crc16;

    CreatureRecord();
    bool validate_crc() const;
    void fix_crc();
    std::array<uint8_t, 20> serialize() const;
    static CreatureRecord deserialize(const std::array<uint8_t, 20>& data);
    std::string name(const std::vector<std::string>& wad_chars) const;
};

} // namespace pox::game

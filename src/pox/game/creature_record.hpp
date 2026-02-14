// Creature record header
#pragma once
#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace pox {
namespace game {

class CreatureRecord {
public:
    CreatureRecord();
    bool validate_crc() const;
    void fix_crc();
    std::array<uint8_t, 20> serialize() const;
    static CreatureRecord deserialize(const std::array<uint8_t, 20>& data);
    std::string get_name(const std::vector<std::string>& wad_chars) const;

    uint8_t head_id;
    uint8_t head_hp;
    uint8_t body_id;
    uint8_t body_hp;
    uint8_t tail_id;
    uint8_t tail_hp;
    std::array<uint8_t, 6> wad_indices;
    std::array<uint8_t, 6> name_indices;
    uint16_t crc16;
};

} // namespace game
} // namespace pox

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
    std::array<uint8_t, 36> serialize() const;
    static CreatureRecord deserialize(const std::array<uint8_t, 36>& data);
    std::string get_name(const std::vector<std::string>& wad_chars) const;

    uint8_t head_id, head_hp;
    uint8_t body_id, body_hp;
    uint8_t legs_id, legs_hp;
    uint8_t shoulders_id, shoulders_hp;
    uint8_t hands_id, hands_hp;
    uint8_t feet_id, feet_hp;
    uint8_t tail_id, tail_hp;
    uint8_t left_arm_id, left_arm_hp;
    uint8_t right_arm_id, right_arm_hp;
    std::array<uint8_t, 6> wad_indices;
    std::array<uint8_t, 6> name_indices;
    uint16_t crc16;
};

} // namespace game
} // namespace pox

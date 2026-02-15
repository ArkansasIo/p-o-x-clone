#ifdef name
#undef name
#endif
#ifdef fix_crc
#undef fix_crc
#endif
#ifdef vector
#undef vector
#endif
#ifdef string
#undef string
#endif
#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <vector>

namespace pox::game {

struct CreatureRecord {
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

    CreatureRecord();
    bool validate_crc() const;
    void fix_crc();
    std::array<uint8_t, 36> serialize() const;
    static CreatureRecord deserialize(const std::array<uint8_t, 36>& data);
    std::string get_name(const std::vector<std::string>& wad_chars) const;
};

} // namespace pox::game

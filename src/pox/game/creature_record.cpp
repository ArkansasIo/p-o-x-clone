#ifdef vector
#undef vector
#endif
#ifdef string
#undef string
#endif
#include "pox/game/creature_record.hpp"

#include "pox/game/crc16.hpp"
#include <cstring>
#include <vector>
#include <string>

namespace pox::game {

CreatureRecord::CreatureRecord()
        : head_id(0), head_hp(0),
            body_id(0), body_hp(0),
            legs_id(0), legs_hp(0),
            shoulders_id(0), shoulders_hp(0),
            hands_id(0), hands_hp(0),
            feet_id(0), feet_hp(0),
            tail_id(0), tail_hp(0),
            left_arm_id(0), left_arm_hp(0),
            right_arm_id(0), right_arm_hp(0),
            crc16(0) {
        wad_indices.fill(0);
        name_indices.fill(0);
}

bool CreatureRecord::validate_crc() const {
    auto data = serialize();
    return crc16_ibm(data.data(), 34) == crc16;
}

void CreatureRecord::fix_crc() {
    auto data = serialize();
    crc16 = crc16_ibm(data.data(), 34);
}

std::array<uint8_t, 36> CreatureRecord::serialize() const {
    std::array<uint8_t, 36> out{};
    out[0] = head_id; out[1] = head_hp;
    out[2] = body_id; out[3] = body_hp;
    out[4] = legs_id; out[5] = legs_hp;
    out[6] = shoulders_id; out[7] = shoulders_hp;
    out[8] = hands_id; out[9] = hands_hp;
    out[10] = feet_id; out[11] = feet_hp;
    out[12] = tail_id; out[13] = tail_hp;
    out[14] = left_arm_id; out[15] = left_arm_hp;
    out[16] = right_arm_id; out[17] = right_arm_hp;
    for (int i = 0; i < 6; ++i) out[18+i] = wad_indices[i];
    for (int i = 0; i < 6; ++i) out[24+i] = name_indices[i];
    out[32] = crc16 & 0xFF;
    out[33] = (crc16 >> 8) & 0xFF;
    // 34,35 unused for now
    return out;
}

CreatureRecord CreatureRecord::deserialize(const std::array<uint8_t, 36>& data) {
    CreatureRecord rec;
    rec.head_id = data[0]; rec.head_hp = data[1];
    rec.body_id = data[2]; rec.body_hp = data[3];
    rec.legs_id = data[4]; rec.legs_hp = data[5];
    rec.shoulders_id = data[6]; rec.shoulders_hp = data[7];
    rec.hands_id = data[8]; rec.hands_hp = data[9];
    rec.feet_id = data[10]; rec.feet_hp = data[11];
    rec.tail_id = data[12]; rec.tail_hp = data[13];
    rec.left_arm_id = data[14]; rec.left_arm_hp = data[15];
    rec.right_arm_id = data[16]; rec.right_arm_hp = data[17];
    for (int i = 0; i < 6; ++i) rec.wad_indices[i] = data[18+i];
    for (int i = 0; i < 6; ++i) rec.name_indices[i] = data[24+i];
    rec.crc16 = data[32] | (data[33] << 8);
    return rec;
}

std::string CreatureRecord::get_name(const std::vector<std::string>& wad_chars) const {
    std::string n;
    for (auto idx : name_indices) {
        if (idx < wad_chars.size()) n += wad_chars[idx];
        else n += '?';
    }
    return n;
}

} // namespace pox::game

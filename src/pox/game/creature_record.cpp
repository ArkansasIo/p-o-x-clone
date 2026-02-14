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

CreatureRecord::CreatureRecord() : head_id(0), head_hp(0), body_id(0), body_hp(0), tail_id(0), tail_hp(0), crc16(0) {
    wad_indices.fill(0);
    name_indices.fill(0);
}

bool CreatureRecord::validate_crc() const {
    auto data = serialize();
    return crc16_ibm(data.data(), 18) == crc16;
}

void CreatureRecord::fix_crc() {
    auto data = serialize();
    crc16 = crc16_ibm(data.data(), 18);
}

std::array<uint8_t, 20> CreatureRecord::serialize() const {
    std::array<uint8_t, 20> out{};
    out[0] = head_id; out[1] = head_hp;
    out[2] = body_id; out[3] = body_hp;
    out[4] = tail_id; out[5] = tail_hp;
    for (int i = 0; i < 6; ++i) out[6+i] = wad_indices[i];
    for (int i = 0; i < 6; ++i) out[12+i] = name_indices[i];
    out[18] = crc16 & 0xFF;
    out[19] = (crc16 >> 8) & 0xFF;
    return out;
}

CreatureRecord CreatureRecord::deserialize(const std::array<uint8_t, 20>& data) {
    CreatureRecord rec;
    rec.head_id = data[0]; rec.head_hp = data[1];
    rec.body_id = data[2]; rec.body_hp = data[3];
    rec.tail_id = data[4]; rec.tail_hp = data[5];
    for (int i = 0; i < 6; ++i) rec.wad_indices[i] = data[6+i];
    for (int i = 0; i < 6; ++i) rec.name_indices[i] = data[12+i];
    rec.crc16 = data[18] | (data[19] << 8);
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

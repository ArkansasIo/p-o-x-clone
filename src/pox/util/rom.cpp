#include "pox/util/rom.hpp"
#include "pox/util/fileio.hpp"
#include "pox/util/checksum.hpp"
#include <cstring>

namespace pox::util {

static bool is_magic_poxr(const std::vector<u8>& d) {
  if (d.size() < 16) return false;
  return d[0]=='P' && d[1]=='O' && d[2]=='X' && d[3]=='R';
}

static u32 read_u32_le(const u8* p) {
  return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

bool load_rom_auto(const std::string& path, std::vector<u8>& out_payload) {
  auto d = read_file(path);
  if (d.empty()) return false;

  if (!is_magic_poxr(d)) {
    out_payload = std::move(d);
    return true;
  }

  const u32 version = read_u32_le(&d[4]);
  (void)version;
  const u32 size = read_u32_le(&d[8]);
  const u32 crc  = read_u32_le(&d[12]);
  if (d.size() < 16ull + size) return false;

  out_payload.assign(d.begin() + 16, d.begin() + 16 + size);
  const u32 got = crc32(out_payload.data(), out_payload.size());
  return got == crc;
}

std::vector<u8> build_poxr(u32 version, const std::vector<u8>& payload) {
  std::vector<u8> out;
  out.reserve(16 + payload.size());
  out.push_back('P'); out.push_back('O'); out.push_back('X'); out.push_back('R');

  auto write_u32 = [&](u32 v) {
    out.push_back((u8)(v & 0xFF));
    out.push_back((u8)((v >> 8) & 0xFF));
    out.push_back((u8)((v >> 16) & 0xFF));
    out.push_back((u8)((v >> 24) & 0xFF));
  };

  write_u32(version);
  write_u32((u32)payload.size());
  const u32 crc = crc32(payload.data(), payload.size());
  write_u32(crc);

  out.insert(out.end(), payload.begin(), payload.end());
  return out;
}

} // namespace pox::util

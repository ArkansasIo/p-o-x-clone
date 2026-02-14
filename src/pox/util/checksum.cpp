#include "pox/util/checksum.hpp"

namespace pox::util {

uint32_t crc32(const void* data, size_t size) {
  const auto* p = (const unsigned char*)data;
  uint32_t crc = 0xFFFFFFFFu;

  for (size_t i = 0; i < size; i++) {
    crc ^= p[i];
    for (int b = 0; b < 8; b++) {
      const uint32_t mask = -(crc & 1u);
      crc = (crc >> 1) ^ (0xEDB88320u & mask);
    }
  }
  return ~crc;
}

} // namespace pox::util

#pragma once
#include <cstdint>
#include <cstddef>

namespace pox::util {
  uint32_t crc32(const void* data, size_t size);
}

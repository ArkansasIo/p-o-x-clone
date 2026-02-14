#include "pox/util/checksum.hpp"
#include <cassert>
#include <cstring>

int test_checksum() {
  const char* s = "hello";
  auto a = pox::util::crc32(s, std::strlen(s));
  auto b = pox::util::crc32(s, std::strlen(s));
  assert(a == b);
  return 0;
}

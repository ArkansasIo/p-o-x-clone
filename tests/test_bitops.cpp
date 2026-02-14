#include "pox/util/bitops.hpp"
#include <cassert>

int test_bitops() {
  using namespace pox::util;
  assert(lo8(0x1234) == 0x34);
  assert(hi8(0x1234) == 0x12);
  assert(make16(0x34, 0x12) == 0x1234);
  pox::u8 v = 0;
  set_bit(v, 3, true);
  assert(test_bit(v, 3));
  set_bit(v, 3, false);
  assert(!test_bit(v, 3));
  return 0;
}

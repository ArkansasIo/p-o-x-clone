#include "pox/util/rom.hpp"
#include <cassert>
#include <vector>

int test_rom_container() {
  std::vector<pox::u8> payload = {1,2,3,4,5,6,7,8,9};
  auto cont = pox::util::build_poxr(1, payload);
  assert(cont.size() == 16 + payload.size());
  assert(cont[0]=='P' && cont[1]=='O' && cont[2]=='X' && cont[3]=='R');
  return 0;
}

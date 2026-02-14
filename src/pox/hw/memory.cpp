#include "pox/hw/memory.hpp"
#include <algorithm>

namespace pox {

void Memory::reset() {
  std::fill(vram_.begin(), vram_.end(), 0);
  std::fill(ram_.begin(),  ram_.end(),  0);
}

} // namespace pox

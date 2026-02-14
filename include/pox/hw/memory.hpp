#pragma once
#include "pox/types.hpp"
#include <array>
#include <cstddef>

namespace pox {

class Memory {
public:
  static constexpr size_t VRAM_SIZE = 0x0800;
  static constexpr size_t RAM_SIZE  = 0x0800;

  void reset();

  u8 vram_read(size_t i) const { return vram_[i % VRAM_SIZE]; }
  void vram_write(size_t i, u8 v) { vram_[i % VRAM_SIZE] = v; }

  u8 ram_read(size_t i) const { return ram_[i % RAM_SIZE]; }
  void ram_write(size_t i, u8 v) { ram_[i % RAM_SIZE] = v; }

  const u8* vram_data() const { return vram_.data(); }

private:
  std::array<u8, VRAM_SIZE> vram_{};
  std::array<u8, RAM_SIZE>  ram_{};
};

} // namespace pox

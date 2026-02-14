#pragma once
#include "pox/types.hpp"
#include <string>
#include <vector>

namespace pox {

class Cartridge {
public:
  bool load(const std::string& rom_path, const std::string& save_prefix);

  u8  read8(u16 addr) const;
  void write8(u16 addr, u8 v);

  u8  sram_read(size_t i) const;
  void sram_write(size_t i, u8 v);

  bool save_sram();

private:
  std::vector<u8> rom_;
  std::vector<u8> sram_;
  std::string sram_path_;
  u8 bank_ = 1;

  bool load_sram_if_present();
};

} // namespace pox

#include "pox/hw/cartridge.hpp"
#include "pox/util/fileio.hpp"
#include "pox/util/rom.hpp"
#include "pox/log.hpp"
#include <filesystem>

namespace pox {

bool Cartridge::load(const std::string& rom_path, const std::string& save_prefix) {
  // Accept either raw ROM or POXR container
  std::vector<u8> payload;
  if (!util::load_rom_auto(rom_path, payload) || payload.empty()) return false;
  rom_ = std::move(payload);

  sram_.assign(8 * 1024, 0); // placeholder
  sram_path_ = save_prefix + ".sav";
  std::filesystem::create_directories(std::filesystem::path(sram_path_).parent_path());
  load_sram_if_present();

  bank_ = 1;
  log::info("ROM loaded: %s (%zu bytes), SRAM: %s (%zu bytes)",
            rom_path.c_str(), rom_.size(), sram_path_.c_str(), sram_.size());
  return true;
}

bool Cartridge::load_sram_if_present() {
  if (sram_path_.empty()) return false;
  if (!std::filesystem::exists(sram_path_)) return false;

  auto d = util::read_file(sram_path_);
  if (d.size() != sram_.size()) {
    log::warn("SRAM size mismatch; ignoring save (got %zu expected %zu)", d.size(), sram_.size());
    return false;
  }
  sram_ = std::move(d);
  return true;
}

bool Cartridge::save_sram() {
  if (sram_path_.empty()) return false;
  return util::write_file(sram_path_, sram_);
}

u8 Cartridge::read8(u16 addr) const {
  if (rom_.empty()) return 0xFF;

  if (addr <= 0x3FFF) {
    const size_t i = addr;
    return (i < rom_.size()) ? rom_[i] : 0xFF;
  }

  if (addr >= 0x4000 && addr <= 0x7FFF) {
    const size_t bank_base = size_t(bank_) * 0x4000;
    const size_t i = bank_base + (addr - 0x4000);
    return (i < rom_.size()) ? rom_[i] : 0xFF;
  }

  return 0xFF;
}

void Cartridge::write8(u16 addr, u8 v) {
  // Placeholder mapper behavior: writes to 0x2000-0x3FFF select bank for 0x4000-0x7FFF.
  if (addr >= 0x2000 && addr <= 0x3FFF) {
    const u8 nb = (v == 0) ? 1 : v;
    bank_ = nb;
  }
}

u8 Cartridge::sram_read(size_t i) const {
  if (sram_.empty()) return 0xFF;
  return sram_[i % sram_.size()];
}

void Cartridge::sram_write(size_t i, u8 v) {
  if (sram_.empty()) return;
  sram_[i % sram_.size()] = v;
}

} // namespace pox

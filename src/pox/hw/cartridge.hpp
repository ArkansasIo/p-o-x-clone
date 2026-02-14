// Cartridge header for POXC auto-mount and boot animation
#pragma once
#include <string>
#include <vector>

namespace pox {

class Cartridge {
public:
    bool load(const std::string& rom_path, const std::string& save_prefix);
    bool load_sram_if_present();
    bool save_sram();
    std::vector<unsigned char> rom_;
    std::vector<unsigned char> sram_;
    std::string sram_path_;
    int bank_;
};

} // namespace pox

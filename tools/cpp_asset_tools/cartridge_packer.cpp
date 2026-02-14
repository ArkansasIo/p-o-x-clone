#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>

uint32_t crc32(const std::vector<uint8_t>& data) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint8_t b : data) {
        crc ^= b;
        for (int i = 0; i < 8; ++i) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    return ~crc;
}
// Cartridge Packer (stub)
// Dev Credit: Stephen Deline Jr
#include <iostream>
int main(int argc, char** argv) {
    if (argc < 6) {
        std::cout << "Usage: cartridge_packer <rom> <wad> <sram> <meta> <output_poxc>\n";
        return 1;
    }
    std::string romPath = argv[1];
    std::string wadPath = argv[2];
    std::string sramPath = argv[3];
    std::string metaPath = argv[4];
    std::string outPath = argv[5];
    std::cout << "Packing cartridge: " << outPath << "\n";
    std::cout << "ROM: " << romPath << "\nWAD: " << wadPath << "\nSRAM: " << sramPath << "\nMETA: " << metaPath << std::endl;
    // Pack files and compute CRC32
    std::vector<uint8_t> cart;
    auto append_file = [&](const std::string& path) {
        std::ifstream in(path, std::ios::binary);
        if (!in) {
            std::cerr << "Failed to open: " << path << std::endl;
            exit(1);
        }
        cart.insert(cart.end(), std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    };
    append_file(romPath);
    append_file(wadPath);
    append_file(sramPath);
    append_file(metaPath);
    uint32_t crc = crc32(cart);
    cart.push_back(crc & 0xFF);
    cart.push_back((crc >> 8) & 0xFF);
    cart.push_back((crc >> 16) & 0xFF);
    cart.push_back((crc >> 24) & 0xFF);
    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outPath << std::endl;
        return 1;
    }
    out.write(reinterpret_cast<const char*>(cart.data()), cart.size());
    out.close();
    std::cout << "Cartridge packed: " << outPath << std::endl;
    return 0;
}

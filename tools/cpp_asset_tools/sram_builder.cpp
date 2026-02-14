#include <fstream>
#include <vector>
#include <array>
#include <cstdint>

uint16_t crc16_ibm(const uint8_t* data, size_t len) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < len; ++i) {
        crc ^= data[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}
// SRAM Builder (stub)
// Dev Credit: Stephen Deline Jr
#include <iostream>
int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: sram_builder <output_sram> <num_slots>\n";
        return 1;
    }
    std::string outPath = argv[1];
    int numSlots = std::stoi(argv[2]);
    std::cout << "Generating SRAM: " << outPath << " with " << numSlots << " slots\n";
    // Generate SRAM image with creature slots and CRC16/IBM
    std::vector<uint8_t> sram;
    for (int i = 0; i < numSlots; ++i) {
        std::array<uint8_t, 20> slot = {0};
        // Example: fill slot with dummy data
        slot[0] = 1; // head_id
        slot[1] = 100; // head_hp
        slot[2] = 2; // body_id
        slot[3] = 100; // body_hp
        slot[4] = 3; // tail_id
        slot[5] = 100; // tail_hp
        // wad_char_index and wad_name_index left as zero
        // Calculate CRC16 over bytes 0..17
        uint16_t crc = crc16_ibm(slot.data(), 18);
        slot[18] = crc & 0xFF;
        slot[19] = (crc >> 8) & 0xFF;
        sram.insert(sram.end(), slot.begin(), slot.end());
    }
    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outPath << std::endl;
        return 1;
    }
    out.write(reinterpret_cast<const char*>(sram.data()), sram.size());
    out.close();
    std::cout << "SRAM generated: " << outPath << std::endl;
    return 0;
}

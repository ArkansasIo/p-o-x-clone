#include "eeprom_storage.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Simulate saving data to EEPROM (file)
void save_to_eeprom(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "[EEPROM] Failed to open file for saving!" << std::endl;
        return;
    }
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
    std::cout << "[EEPROM] Data saved to " << filename << std::endl;
}

// Simulate loading data from EEPROM (file)
std::vector<uint8_t> load_from_eeprom(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "[EEPROM] Failed to open file for loading!" << std::endl;
        return {};
    }
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::cout << "[EEPROM] Data loaded from " << filename << ", size: " << data.size() << " bytes." << std::endl;
    return data;
}

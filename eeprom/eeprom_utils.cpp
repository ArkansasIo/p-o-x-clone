#include "eeprom_utils.hpp"
#include <iostream>
#include <fstream>
#include <string>

// Simulate erasing EEPROM (delete file)
void erase_eeprom(const std::string& filename) {
    if (std::remove(filename.c_str()) == 0) {
        std::cout << "[EEPROM] EEPROM file " << filename << " erased." << std::endl;
    } else {
        std::cerr << "[EEPROM] Failed to erase EEPROM file!" << std::endl;
    }
}

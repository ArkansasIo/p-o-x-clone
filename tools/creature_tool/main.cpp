#include "pox/game/creature_record.hpp"
#include "creature_tool.hpp"
#include <iostream>
#include <fstream>
#include <array>

using namespace pox::game;

int main(int argc, char** argv) {
    pox_tool::CreatureTool tool;
    // Example usage
    tool.addCreature(pox::game::Creature("Sample", pox::game::Creature::Type::Humanoid, pox::game::Creature::SubType::None, pox::game::Creature::Race::Human));
    tool.save("creatures.dat");
    tool.load("creatures.dat");

    if (argc < 3) {
        std::cout << "Usage: pox_creature_tool <cmd> <file>\n";
        std::cout << "Commands: dump, validate, fixcrc\n";
        return 1;
    }
    std::string cmd = argv[1], file = argv[2];
    if (cmd == "dump") {
        std::ifstream f(file, std::ios::binary);
        std::array<uint8_t, 36> data{};
        f.read((char*)data.data(), 20);
        auto rec = CreatureRecord::deserialize(data);
        std::cout << "Head: " << int(rec.head_id) << " HP: " << int(rec.head_hp) << "\n";
        std::cout << "Body: " << int(rec.body_id) << " HP: " << int(rec.body_hp) << "\n";
        std::cout << "Tail: " << int(rec.tail_id) << " HP: " << int(rec.tail_hp) << "\n";
        std::cout << "WAD indices: ";
        for (auto w : rec.wad_indices) std::cout << int(w) << ' ';
        std::cout << "\nName indices: ";
        for (auto n : rec.name_indices) std::cout << int(n) << ' ';
        std::cout << "\nCRC16: 0x" << std::hex << rec.crc16 << std::dec << "\n";
        std::cout << "CRC valid: " << (rec.validate_crc() ? "yes" : "no") << "\n";
    } else if (cmd == "validate") {
        std::ifstream f(file, std::ios::binary);
        std::array<uint8_t, 36> data{};
        f.read((char*)data.data(), 20);
        auto rec = CreatureRecord::deserialize(data);
        std::cout << (rec.validate_crc() ? "Valid\n" : "Invalid\n");
    } else if (cmd == "fixcrc") {
        if (argc < 4) {
            std::cout << "Usage: pox_creature_tool fixcrc <infile> <outfile>\n";
            return 1;
        }
        std::ifstream f(file, std::ios::binary);
        std::array<uint8_t, 36> data{};
        f.read((char*)data.data(), 20);
        auto rec = CreatureRecord::deserialize(data);
        rec.fix_crc();
        auto out = rec.serialize();
        std::ofstream o(argv[3], std::ios::binary);
        o.write((char*)out.data(), 20);
        std::cout << "CRC fixed and written to " << argv[3] << "\n";
    } else {
        std::cout << "Unknown command\n";
        return 1;
    }
    return 0;
}

// pox_packer.cpp (C++ version of Node.js tool)
// Dev Credit: Stephen Deline Jr
// Creates a POXC cartridge container that bundles: ROM (.poxr or raw), WAD, SRAM image, and metadata.
// Layout:
// 0x00  'POXC' (4)
// 0x04  uint32_t version = 1
// 0x08  uint32_t romOffset
// 0x0C  uint32_t romSize
// 0x10  uint32_t wadOffset
// 0x14  uint32_t wadSize
// 0x18  uint32_t sramOffset
// 0x1C  uint32_t sramSize
// 0x20  uint32_t metaOffset
// 0x24  uint32_t metaSize
// 0x28  uint32_t crc32(payload from 0x00..end, crc field treated as 0)
// 0x2C  reserved (uint32_t) = 0
// 0x30  payload blobs packed back-to-back

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>

uint32_t crc32(const std::vector<uint8_t>& buf) {
    uint32_t c = 0xFFFFFFFF;
    for (uint8_t b : buf) {
        c ^= b;
        for (int k = 0; k < 8; ++k) {
            uint32_t m = -(c & 1);
            c = (c >> 1) ^ (0xEDB88320 & m);
        }
    }
    return (c ^ 0xFFFFFFFF);
}

void write_u32le(std::vector<uint8_t>& out, size_t offset, uint32_t v) {
    out[offset+0] = v & 0xFF;
    out[offset+1] = (v >> 8) & 0xFF;
    out[offset+2] = (v >> 16) & 0xFF;
    out[offset+3] = (v >> 24) & 0xFF;
}

std::vector<uint8_t> read_file(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Failed to open " + path);
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    f.seekg(0, std::ios::beg);
    std::vector<uint8_t> buf(size);
    f.read(reinterpret_cast<char*>(buf.data()), size);
    return buf;
}

void write_file(const std::string& path, const std::vector<uint8_t>& buf) {
    std::filesystem::create_directories(std::filesystem::path(path).parent_path());
    std::ofstream f(path, std::ios::binary);
    f.write(reinterpret_cast<const char*>(buf.data()), buf.size());
}

int main(int argc, char** argv) {
    if (argc != 11 || std::string(argv[1]) != "pack") {
        std::cout << "Usage:\n  pox_packer pack --rom <rom> --wad <wad> --sram <sram> --meta <meta> --out <out>\n";
        return 1;
    }
    std::string romPath, wadPath, sramPath, metaPath, outPath;
    for (int i = 2; i < argc; i += 2) {
        std::string key = argv[i];
        std::string val = argv[i+1];
        if (key == "--rom") romPath = val;
        else if (key == "--wad") wadPath = val;
        else if (key == "--sram") sramPath = val;
        else if (key == "--meta") metaPath = val;
        else if (key == "--out") outPath = val;
    }
    auto rom = read_file(romPath);
    auto wad = read_file(wadPath);
    auto sram = read_file(sramPath);
    auto meta = read_file(metaPath);

    const size_t headerSize = 0x30;
    size_t off = headerSize;
    size_t romOffset = off; off += rom.size();
    size_t wadOffset = off; off += wad.size();
    size_t sramOffset = off; off += sram.size();
    size_t metaOffset = off; off += meta.size();

    size_t totalSize = off;
    std::vector<uint8_t> out(totalSize);
    std::memcpy(out.data(), "POXC", 4);
    write_u32le(out, 0x04, 1);
    write_u32le(out, 0x08, static_cast<uint32_t>(romOffset));
    write_u32le(out, 0x0C, static_cast<uint32_t>(rom.size()));
    write_u32le(out, 0x10, static_cast<uint32_t>(wadOffset));
    write_u32le(out, 0x14, static_cast<uint32_t>(wad.size()));
    write_u32le(out, 0x18, static_cast<uint32_t>(sramOffset));
    write_u32le(out, 0x1C, static_cast<uint32_t>(sram.size()));
    write_u32le(out, 0x20, static_cast<uint32_t>(metaOffset));
    write_u32le(out, 0x24, static_cast<uint32_t>(meta.size()));
    write_u32le(out, 0x28, 0); // placeholder CRC
    write_u32le(out, 0x2C, 0);
    std::memcpy(out.data() + romOffset, rom.data(), rom.size());
    std::memcpy(out.data() + wadOffset, wad.data(), wad.size());
    std::memcpy(out.data() + sramOffset, sram.data(), sram.size());
    std::memcpy(out.data() + metaOffset, meta.data(), meta.size());
    uint32_t crc = crc32(out);
    write_u32le(out, 0x28, crc);
    write_file(outPath, out);
    std::cout << "POXC written: " << outPath << "\n";
    std::cout << " rom " << rom.size() << " bytes, wad " << wad.size() << ", sram " << sram.size() << ", meta " << meta.size() << "\n";
    std::cout << " crc32=0x" << std::hex << crc << std::dec << "\n";
    return 0;
}

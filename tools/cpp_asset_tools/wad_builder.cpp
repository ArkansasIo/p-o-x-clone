#include <fstream>
#include <vector>
#include <string>
#include <cstring>

struct Lump {
    std::string name;
    std::vector<uint8_t> data;
};

void write_wad(const std::string& outPath, const std::vector<Lump>& lumps) {
    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outPath << std::endl;
        return;
    }
    // Write header: 'PWAD', lump count, directory offset
    out.write("PWAD", 4);
    uint32_t lumpCount = static_cast<uint32_t>(lumps.size());
    uint32_t dirOffset = 12;
    for (const auto& lump : lumps) dirOffset += static_cast<uint32_t>(lump.data.size());
    out.write(reinterpret_cast<const char*>(&lumpCount), 4);
    out.write(reinterpret_cast<const char*>(&dirOffset), 4);
    // Write lumps
    for (const auto& lump : lumps) {
        out.write(reinterpret_cast<const char*>(lump.data.data()), lump.data.size());
    }
    // Write directory
    uint32_t offset = 12;
    for (const auto& lump : lumps) {
        out.write(reinterpret_cast<const char*>(&offset), 4);
        uint32_t size = static_cast<uint32_t>(lump.data.size());
        out.write(reinterpret_cast<const char*>(&size), 4);
        char name[8] = {0};
        std::strncpy(name, lump.name.c_str(), 8);
        out.write(name, 8);
        offset += size;
    }
    out.close();
}
// WAD Builder (stub)
// Dev Credit: Stephen Deline Jr
#include <iostream>
int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: wad_builder <asset_dir> <output_wad>\n";
        return 1;
    }
    std::string assetDir = argv[1];
    std::string outPath = argv[2];
    std::cout << "Packing assets from: " << assetDir << " into: " << outPath << std::endl;
    std::vector<Lump> lumps;
    // Example: Add META lump
    std::string meta = "POX WAD META\n";
    lumps.push_back({"META", std::vector<uint8_t>(meta.begin(), meta.end())});

    // Placeholder: Add IMG2BPP lump
    std::string img2bpp = "IMG2BPP placeholder data\n";
    lumps.push_back({"IMG2BPP", std::vector<uint8_t>(img2bpp.begin(), img2bpp.end())});

    // Placeholder: Add TILES2BPP lump
    std::string tiles2bpp = "TILES2BPP placeholder data\n";
    lumps.push_back({"TILES2BPP", std::vector<uint8_t>(tiles2bpp.begin(), tiles2bpp.end())});

    // TODO: Scan assetDir and replace placeholders with real asset data
    write_wad(outPath, lumps);
    std::cout << "WAD built: " << outPath << std::endl;
    return 0;
}

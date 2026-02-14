#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

// Stub audio converter: accepts a simple text tone script and emits bytes.
// Tone script lines: <enable 0/1> <volume 0-255> <period 0-65535>
//
// This matches the placeholder Audio IO registers:
// 0x00 enable, 0x01 volume, 0x02 period lo, 0x03 period hi
//
// Replace with real PO-X audio format/hardware.

static bool write_file(const std::string& path, const std::vector<uint8_t>& data) {
  std::ofstream f(path, std::ios::binary);
  if (!f) return false;
  f.write((const char*)data.data(), (std::streamsize)data.size());
  return true;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    std::printf("Usage: pox_audio_converter <tone_script.txt> <out.bin>\n");
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in) { std::printf("Failed to open %s\n", argv[1]); return 1; }

  std::vector<uint8_t> out;
  int enable=0, vol=0;
  int period=0;

  while (in >> enable >> vol >> period) {
    out.push_back((uint8_t)(enable ? 1 : 0));
    out.push_back((uint8_t)(vol & 0xFF));
    out.push_back((uint8_t)(period & 0xFF));
    out.push_back((uint8_t)((period >> 8) & 0xFF));
  }

  if (!write_file(argv[2], out)) {
    std::printf("Failed to write %s\n", argv[2]); return 1;
  }

  std::printf("Wrote %s (%zu bytes)\n", argv[2], out.size());
  return 0;
}

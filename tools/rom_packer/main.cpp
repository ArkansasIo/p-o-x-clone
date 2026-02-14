#include "pox/util/fileio.hpp"
#include "pox/util/rom.hpp"
#include <cstdio>

int main(int argc, char** argv) {
  if (argc < 3) {
    std::printf("Usage: pox_rom_packer <in_raw_rom.bin> <out.poxr>\n");
    return 1;
  }

  auto payload = pox::util::read_file(argv[1]);
  if (payload.empty()) {
    std::printf("Failed to read %s\n", argv[1]);
    return 1;
  }

  auto out = pox::util::build_poxr(1, payload);
  if (!pox::util::write_file(argv[2], out)) {
    std::printf("Failed to write %s\n", argv[2]);
    return 1;
  }

  std::printf("Wrote %s (%zu bytes)\n", argv[2], out.size());
  return 0;
}

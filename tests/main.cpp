#include <cstdio>

int test_bitops();
int test_checksum();
int test_rom_container();
int test_cpu_decode_smoke();

int main() {
  int fails = 0;
  fails += test_bitops();
  fails += test_checksum();
  fails += test_rom_container();
  fails += test_cpu_decode_smoke();

  // New feature tests
  extern int test_creature_extended();
  extern int test_biome_framework();
  extern int test_csv_data();
  fails += test_creature_extended();
  fails += test_biome_framework();
  fails += test_csv_data();

  if (fails == 0) {
    std::printf("All tests passed.\n");
    return 0;
  }
  std::printf("%d tests failed.\n", fails);
  return 1;
}

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

  if (fails == 0) {
    std::printf("All tests passed.\n");
    return 0;
  }
  std::printf("%d tests failed.\n", fails);
  return 1;
}

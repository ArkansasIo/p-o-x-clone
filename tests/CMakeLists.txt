add_executable(pox_tests
  main.cpp
  test_bitops.cpp
  test_checksum.cpp
  test_rom_container.cpp
  test_cpu_decode_smoke.cpp
)

target_include_directories(pox_tests PRIVATE ../include)
target_link_libraries(pox_tests PRIVATE pox_core)

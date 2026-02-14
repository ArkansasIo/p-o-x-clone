

enable_testing()
add_executable(pox_tests
  test_bitops.cpp
  test_checksum.cpp
  test_rom_container.cpp
  test_cpu_decode_smoke.cpp
  test_creature_db.cpp
)

target_include_directories(pox_tests PRIVATE ../include)
target_link_libraries(pox_tests PRIVATE pox_core)

add_test(NAME pox_tests COMMAND pox_tests)

target_include_directories(pox_tests PRIVATE ../include)
target_link_libraries(pox_tests PRIVATE pox_core)

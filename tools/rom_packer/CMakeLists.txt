add_executable(pox_rom_packer main.cpp)
target_include_directories(pox_rom_packer PRIVATE ../../include)
target_link_libraries(pox_rom_packer PRIVATE pox_core)

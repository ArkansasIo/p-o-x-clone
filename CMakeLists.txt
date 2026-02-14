cmake_minimum_required(VERSION 3.22)
project(pox_clone LANGUAGES CXX)

# Add custom CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(pox_core
  src/pox/pox.cpp
  src/pox/log.cpp

  src/pox/core/bus.cpp
  src/pox/core/clock.cpp
  src/pox/core/events.cpp

  src/pox/hw/cpu8.cpp
  src/pox/hw/memory.cpp
  src/pox/hw/timer.cpp
  src/pox/hw/input.cpp
  src/pox/hw/display.cpp
  src/pox/hw/audio.cpp
  src/pox/hw/power.cpp
  src/pox/hw/cartridge.cpp

  src/pox/util/rom.cpp
  src/pox/util/checksum.cpp
  src/pox/util/serialize.cpp
  src/pox/util/fileio.cpp

  src/pox/game/creature_db.cpp
  src/pox/game/crc16.cpp
  src/pox/game/creature_record.cpp
  src/pox/game/creature_runtime.cpp
  src/pox/game/wad_resources.cpp

  src/pox/debug/trace.cpp
  src/pox/debug/debugger.cpp
  src/pox/debug/disasm.cpp
)

target_include_directories(pox_core PUBLIC include)

option(POX_BUILD_SDL "Build SDL2 desktop frontend" ON)
if(POX_BUILD_SDL)
  add_subdirectory(apps/desktop_sdl)
endif()
add_subdirectory(tools/rom_packer)
add_subdirectory(tools/sprite_converter)
add_subdirectory(tools/audio_converter)
add_subdirectory(tests)

# Install asset folders from packs to build output
install(DIRECTORY pox-combat-pack-v2/atlases DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-combat-pack-v2/atlases)
install(DIRECTORY pox-combat-pack-v2/sprites DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-combat-pack-v2/sprites)
install(FILES pox-combat-pack-v2/atlas_map.json pox-combat-pack-v2/manifest.json DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-combat-pack-v2)

install(DIRECTORY pox-master-library/atlases DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-master-library/atlases)
install(DIRECTORY pox-master-library/sprites DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-master-library/sprites)
install(FILES pox-master-library/atlas_map.json pox-master-library/manifest.json DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-master-library)

install(DIRECTORY pox-ultimate-production-pack/atlases DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-ultimate-production-pack/atlases)
install(DIRECTORY pox-ultimate-production-pack/sprites DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-ultimate-production-pack/sprites)
install(FILES pox-ultimate-production-pack/atlas_map.json pox-ultimate-production-pack/manifest.json DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-ultimate-production-pack)

install(DIRECTORY pox-final-cartridge-system/assets DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-final-cartridge-system/assets)
install(DIRECTORY pox-final-cartridge-system/docs DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-final-cartridge-system/docs)
install(DIRECTORY pox-final-cartridge-system/examples DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-final-cartridge-system/examples)
install(DIRECTORY pox-final-cartridge-system/scripts DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-final-cartridge-system/scripts)
install(DIRECTORY pox-final-cartridge-system/tools DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-final-cartridge-system/tools)
install(FILES pox-final-cartridge-system/README.md DESTINATION ${CMAKE_BINARY_DIR}/assets/pox-final-cartridge-system)

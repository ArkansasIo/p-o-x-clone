project(pox_desktop_sdl LANGUAGES CXX)


# Manually specify SDL2 paths if not found
set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SDL2-devel-2.30.2-VC/SDL2-2.30.2/include")
set(SDL2_LIBRARY "${CMAKE_SOURCE_DIR}/SDL2-devel-2.30.2-VC/SDL2-2.30.2/lib/x64/SDL2.lib")
set(SDL2MAIN_LIBRARY "${CMAKE_SOURCE_DIR}/SDL2-devel-2.30.2-VC/SDL2-2.30.2/lib/x64/SDL2main.lib")

include_directories(${SDL2_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})

add_executable(pox_desktop
  main.cpp
  sdl_video.cpp
  sdl_video.hpp
  sdl_input.cpp
  sdl_input.hpp
  sdl_audio.cpp
  sdl_audio.hpp
)

# Ensure console subsystem for main()
if (MSVC)
  set_target_properties(pox_desktop PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()

target_include_directories(pox_desktop PRIVATE ../../include)
target_link_libraries(pox_desktop PRIVATE pox_core ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})
target_include_directories(pox_desktop PRIVATE ${SDL2_INCLUDE_DIR})

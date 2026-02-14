# FindSDL2.cmake
# Minimal CMake module to help find SDL2 on Windows

find_path(SDL2_INCLUDE_DIR SDL.h
    PATHS
        $ENV{SDL2_DIR}/include
        ${SDL2_DIR}/include
        C:/SDL2/include
        C:/Program Files/SDL2/include
)

find_library(SDL2_LIBRARY NAMES SDL2 SDL2main
    PATHS
        $ENV{SDL2_DIR}/lib/x64
        ${SDL2_DIR}/lib/x64
        $ENV{SDL2_DIR}/lib
        ${SDL2_DIR}/lib
        C:/SDL2/lib/x64
        C:/SDL2/lib
        C:/Program Files/SDL2/lib/x64
        C:/Program Files/SDL2/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_LIBRARY SDL2_INCLUDE_DIR)

if(SDL2_FOUND)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY})
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
endif()

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)

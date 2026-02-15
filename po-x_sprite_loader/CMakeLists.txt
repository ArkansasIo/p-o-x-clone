cmake_minimum_required(VERSION 3.14)
project(pox_sprite_loader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pox_sprite_loader main.cpp pox1_loader.cpp pox1_loader.hpp sprite_decoder.cpp sprite_decoder.hpp)

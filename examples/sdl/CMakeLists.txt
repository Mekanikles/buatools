cmake_minimum_required(VERSION 3.9)

find_package(fmt REQUIRED)
find_package(sdl2 REQUIRED)
find_package(eastl REQUIRED)

add_executable(example_sdl example_sdl.cpp)
target_link_libraries(example_sdl buacore imbua fmt::fmt EASTL::EASTL SDL2::SDL2main)

cmake_minimum_required(VERSION 3.9)

find_package(fmt REQUIRED)
find_package(sdl2 REQUIRED)
find_package(eastl REQUIRED)

# TODO: buacore dependency should be transitive

add_executable(example_sdl_retained sdlshared.cpp example_sdl_retained.cpp)
target_link_libraries(example_sdl_retained buacore buaelements fmt::fmt EASTL::EASTL SDL2::SDL2main)

add_executable(example_sdl_im sdlshared.cpp example_sdl_im.cpp)
target_link_libraries(example_sdl_im buacore imbua fmt::fmt EASTL::EASTL SDL2::SDL2main)


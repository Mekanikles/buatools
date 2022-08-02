cmake_minimum_required(VERSION 3.9)

add_library(imbua src/fill.cpp src/imbua.cpp src/imstate.cpp)
target_include_directories(imbua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

# EASTL should be depended on transitiely here, via bualib, I'm not sure why it isn't
find_package(eastl REQUIRED)

target_link_libraries(imbua bualib buaelements EASTL::EASTL)
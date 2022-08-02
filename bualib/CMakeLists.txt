cmake_minimum_required(VERSION 3.9)

add_library(bualib src/bua.cpp)
target_include_directories(bualib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

find_package(eastl REQUIRED)

target_link_libraries(bualib buacore EASTL::EASTL)
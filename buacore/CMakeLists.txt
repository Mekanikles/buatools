cmake_minimum_required(VERSION 3.9)

find_package(Microsoft.GSL)

add_library(buacore src/core.cpp)
target_include_directories(buacore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

target_link_libraries(buacore Microsoft.GSL::GSL)

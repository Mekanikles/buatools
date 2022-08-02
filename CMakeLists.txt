cmake_minimum_required(VERSION 3.9)
project(BuaTools CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions("-std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure conan api is available
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
		"${CMAKE_BINARY_DIR}/conan.cmake"
		TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# Add external dependencies here
# TODO: This is the unified set of all dependencies, which is
#	not very practical. See if eash sub directory can delcare
#	their own external dependencies
set(requirements "
	fmt/6.1.2 
	sdl/2.0.20
	eastl/3.18.00
	ms-gsl/4.0.0
	")

# Ensure dependencies are installed
conan_cmake_configure(
	REQUIRES ${requirements}
	GENERATORS cmake_find_package)
conan_cmake_autodetect(settings)
conan_cmake_install(
	PATH_OR_REFERENCE .
	BUILD missing
	REMOTE conancenter
	SETTINGS ${settings})

# TODO: Only in debug
add_compile_definitions(EASTL_DEBUGPARAMS_LEVEL=3)

# Recurse into sub directories
add_subdirectory(buacore)
add_subdirectory(bualib)
add_subdirectory(buaelements)
add_subdirectory(imbua)
add_subdirectory(examples)
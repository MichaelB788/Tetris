# Cmake configuration
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Installs Catch2 by fetching the github repo if on Linux

# Project details
project(
	Tetris
	VERSION 1.0
	DESCRIPTION "Tetris remade with C++ and SDL2"
	LANGUAGES CXX
)

# Subdirectories
add_subdirectory(src/core)
# NOTE: The render and app modules are not yet ready for implementation.
# add_subdirectory(src/app)
# add_subdirectory(src/render)

# Enable testing in debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	find_package(Catch2 3 REQUIRED)

	if (NOT Catch2_FOUND AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
		add_subdirectory(extern/)
	endif()

	enable_testing()
	add_subdirectory(tests/core)
	# add_subdirectory(tests/render)
	# add_subdirectory(tests/app)
endif()
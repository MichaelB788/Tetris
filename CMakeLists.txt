# Cmake configuration
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project details
project(
	Tetris
	VERSION 1.0
	DESCRIPTION "Tetris remade with C++ and SDL2"
	LANGUAGES CXX
)
enable_testing()

# Subdirectories
add_subdirectory(src/core)
# NOTE: The render and app modules are not yet ready for implementation.
# add_subdirectory(src/app)
# add_subdirectory(src/render)

# Tests
add_subdirectory(tests/core)
# add_subdirectory(tests/app)
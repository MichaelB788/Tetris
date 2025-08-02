cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
	Tetris
	VERSION 1.0
	DESCRIPTION "Tetris remade with C++ and SDL2"
	LANGUAGES CXX
)

add_subdirectory(src/core)
add_subdirectory(src/app)
add_subdirectory(src/render)
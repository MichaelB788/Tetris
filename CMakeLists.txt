cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
	Tetris
	VERSION 3.0
	DESCRIPTION "A Tetris clone made with SDL3"
	LANGUAGES CXX
)

include_directories(BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include {CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

add_subdirectory(src)
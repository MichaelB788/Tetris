# CMake version required
cmake_minimum_required(VERSION 3.0)

# Project
project(Tetris VERSION 1.0.0
    DESCRIPTION "A game inspired by a renowned classic")

# CMake configuration options
# Compiler used is g++ as it works best with SDL2
set(CMAKE_C_COMPILER "g++")

# Make sure CMake uses the C++ standard (C++11 and above)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} "-lSDL2 -lSDL2main")

# Library to use (All of the components and game objects under src/)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} GameLibrary)


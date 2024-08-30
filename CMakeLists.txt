cmake_minimum_required(VERSION 3.0)
project(block_game)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-lSDL2")
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} GameLibrary)


cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
	Tetris
	VERSION 2.0
	DESCRIPTION "Tetris remade with C++ and SDL2"
	LANGUAGES CXX
)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/include)

add_subdirectory(src/util)
add_subdirectory(src/core)
add_subdirectory(src/render)
add_subdirectory(src/app)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	find_package(Catch2 3 REQUIRED)

  if (NOT Catch2_FOUND AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(extern/)
  endif()

  enable_testing()
  add_subdirectory(tests/core)
endif()

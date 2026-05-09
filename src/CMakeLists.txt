set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
  PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

add_subdirectory(core)
add_subdirectory(platform)
add_subdirectory(render)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  Tetris::Core
  Tetris::Platform
  Tetris::Render
)


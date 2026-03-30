set(BINARY_NAME ${CMAKE_PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(${BINARY_NAME} main.cpp)

add_subdirectory(util)
add_subdirectory(core)
add_subdirectory(platform)
add_subdirectory(render)

target_link_libraries(${BINARY_NAME} PRIVATE
  Tetris::Core
  Tetris::Platform
  Tetris::Render
)

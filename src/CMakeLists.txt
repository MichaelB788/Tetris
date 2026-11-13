# ensure dependencies are installed
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# library
set(SOURCE_LIB ${CMAKE_PROJECT_NAME}Source)

add_library(${SOURCE_LIB}
  App.cpp
  Geometry.cpp
  KeyboardListener.cpp
  Piece.cpp
  PlatformSDL.cpp
  PlatformSDL_TTF.cpp
  Playfield.cpp
  SevenBag.cpp
  Tetris.cpp
  TetrisRenderer.cpp
  Timer.cpp
)

target_include_directories(${SOURCE_LIB} PUBLIC
  ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(${SOURCE_LIB} PUBLIC
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  SDL3_image::SDL3_image
)

# executable
set(EXE ${CMAKE_PROJECT_NAME})

add_executable(${EXE} main.cpp)

target_compile_definitions(${EXE} PRIVATE
  PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

target_compile_options(${EXE} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(${EXE} PRIVATE ${SOURCE_LIB})

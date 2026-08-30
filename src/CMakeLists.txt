add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
  PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_library(TetrisSource
  App.cpp
  AppRenderer.cpp
  EventHandler.cpp
  LockDelay.cpp
  Matrix.cpp
  PlatformSDL.cpp
  PlatformSDL_TTF.cpp
  SevenBag.cpp
  Tetris.cpp
  Tetromino.cpp
  TextRenderer.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  TetrisSource
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  SDL3_image::SDL3_image
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
  PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

add_library(TetrisSource
  AppState.cpp
  EventHandler.cpp
  FPS.cpp
  LockDelay.cpp
  Matrix.cpp
  NumberRenderer.cpp
  PlatformSDL.cpp
  PlatformSDL_TTF.cpp
  ScreenPos.cpp
  SevenBag.cpp
  Tetris.cpp
  TetrisRenderer.cpp
  Tetromino.cpp
  TextRenderer.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  TetrisSource
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  SDL3_image::SDL3_image
)

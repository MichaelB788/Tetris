add_library(TetrisPlatform
  EventHandler.cpp
  PlatformSDL.cpp
  PlatformSDL_IMG.cpp
  PlatformSDL_TTF.cpp
)
add_library(Tetris::Platform ALIAS TetrisPlatform)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

target_link_libraries(TetrisPlatform PRIVATE
  Tetris::Core
  SDL3::SDL3
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
)

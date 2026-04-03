add_library(TetrisRender
  BoardRenderer.cpp
  HUDRenderer.cpp
  TextRenderer.cpp
  Tetris_Paint.cpp
)
add_library(Tetris::Render ALIAS TetrisRender)

target_link_libraries(TetrisRender PRIVATE
  Tetris::Core
  Tetris::Platform
)

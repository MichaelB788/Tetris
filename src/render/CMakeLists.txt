add_library(TetrisRender
  TetrisGameRenderer.cpp
  Tetris_Paint.cpp
)
add_library(Tetris::Render ALIAS TetrisRender)

target_link_libraries(TetrisRender PRIVATE
  Tetris::Core
  Tetris::Platform
)

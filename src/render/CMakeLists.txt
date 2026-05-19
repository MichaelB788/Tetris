add_library(TetrisRender
  GameRenderer.cpp
  TextRenderer.cpp
)
add_library(Tetris::Render ALIAS TetrisRender)

target_link_libraries(TetrisRender PRIVATE
  Tetris::Core
  Tetris::Platform
)

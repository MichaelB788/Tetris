add_library(TetrisRender
  BoardRenderer.cpp
  HUDRenderer.cpp
  TextRenderer.cpp
  tetris-paint.cpp
)
add_library(Tetris::Render ALIAS TetrisRender)

target_link_libraries(TetrisRender PRIVATE
  Tetris::Core
  Tetris::Platform
)

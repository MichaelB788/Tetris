add_library(TetrisCore
  Matrix.cpp
  SevenBag.cpp
  Tetris.cpp
  App.cpp
  Tetromino.cpp
)
add_library(Tetris::Core ALIAS TetrisCore)

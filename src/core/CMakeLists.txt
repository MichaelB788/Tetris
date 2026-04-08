add_library(TetrisCore
  Matrix.cpp
  NextQueue.cpp
  TetrisGame.cpp
  TetrisApp.cpp
  Tetromino.cpp
  Tetris_Move.cpp
)
add_library(Tetris::Core ALIAS TetrisCore)

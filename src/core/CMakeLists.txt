add_library(TetrisCore
  Matrix.cpp
  NextQueue.cpp
  TetrisGame.cpp
  TetrisApp.cpp
  Tetromino.cpp
)
add_library(Tetris::Core ALIAS TetrisCore)

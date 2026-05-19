add_library(TetrisCore
  Matrix.cpp
  NextQueue.cpp
  Tetris.cpp
  App.cpp
  Tetromino.cpp
)
add_library(Tetris::Core ALIAS TetrisCore)

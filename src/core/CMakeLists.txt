add_library(tetris_core
  tetromino.cpp
  tetromino-operations.cpp
  matrix.cpp
)
add_library(Tetris::Core ALIAS tetris_core)

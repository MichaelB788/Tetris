add_library(tetris_core
  matrix.cpp
	matrix-operations.cpp
  tetromino.cpp
  tetromino-operations.cpp
)
add_library(Tetris::Core ALIAS tetris_core)

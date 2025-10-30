add_library(tetris_core
	shape.cpp
  tetromino.cpp
  matrix.cpp
)
add_library(Tetris::Core ALIAS tetris_core)

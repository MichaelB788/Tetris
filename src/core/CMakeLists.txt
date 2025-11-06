add_library(tetris_core
  tetromino.cpp
  matrix.cpp
)
add_library(Tetris::Core ALIAS tetris_core)

target_link_libraries(tetris_core PRIVATE
	Tetris::Utilities
)

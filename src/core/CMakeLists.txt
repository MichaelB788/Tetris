add_library(tetris_core
	tetromino-generator.cpp
  tetromino.cpp
	tetromino-movement.cpp
	tetromino-management.cpp
	super-rotation-system.cpp
  matrix.cpp
	game-state.cpp
	event-handler.cpp
)
add_library(Tetris::Core ALIAS tetris_core)

target_link_libraries(tetris_core PRIVATE
	Tetris::Utilities
)

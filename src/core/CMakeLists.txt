add_library(tetris_core
	# TODO: Add Command, EventHandler, Tetromino
	src/Playfield.cpp
)

target_include_directories(tetris_core PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/tetris_core>
)

add_library(tetris-render 
	matrix-renderer.cpp
	tetromino-renderer.cpp
	text-renderer.cpp
	ui-renderer.cpp
)
add_library(Tetris::Renderer ALIAS tetris-render)

target_link_libraries(tetris-render PRIVATE
	Tetris::Core
	Tetris::Utilities
)

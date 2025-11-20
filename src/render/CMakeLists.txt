add_library(tetris-render 
	tetris-renderer.cpp
	ui.cpp
)
add_library(Tetris::Renderer ALIAS tetris-render)

target_link_libraries(tetris-render PRIVATE
	Tetris::Core
	Tetris::Utilities
)

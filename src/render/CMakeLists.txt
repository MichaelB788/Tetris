add_library(tetris-render 
	matrix-renderer.cpp
)
add_library(Tetris::Renderer ALIAS tetris-render)

target_link_libraries(tetris-render PRIVATE
	Tetris::Core
	Tetris::Utilities
)

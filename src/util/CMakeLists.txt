add_library(utility_objects
	ring-buffer.cpp
	geometry.cpp
	window.cpp
	renderer.cpp
	text.cpp
	color.cpp
)
add_library(Tetris::Utilities ALIAS utility_objects)

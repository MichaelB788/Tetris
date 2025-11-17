add_library(utility_objects
	geometry.cpp
	window.cpp
	renderer.cpp
	text.cpp
)
add_library(Tetris::Utilities ALIAS utility_objects)

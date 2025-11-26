add_library(utility_objects
	geometry.cpp
	window.cpp
	renderer.cpp
	color.cpp
)
add_library(Tetris::Utilities ALIAS utility_objects)

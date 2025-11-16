add_library(utility_objects
	vector2.cpp
	window.cpp
	renderer.cpp
	text.cpp
)
add_library(Tetris::Utilities ALIAS utility_objects)

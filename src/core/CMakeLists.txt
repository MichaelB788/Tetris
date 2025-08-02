# TODO: finish this
set(CORE_HEADERS
	include/Command.hpp
	include/Coordinate.hpp
	include/Drop.hpp
	include/EventHandler.hpp
)

add_library(TetrisCoreLibrary STATIC
	CORE_HEADERS
)

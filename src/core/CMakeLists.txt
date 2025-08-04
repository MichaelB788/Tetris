# TODO: finish this
set(CORE_HEADERS
	include/Board.hpp
	include/Command.hpp
	include/Coordinate.hpp
	include/EventHandler.hpp
	include/GameConstants.hpp
	include/Mechanics.hpp
	include/Tetromino.hpp
)

set(CORE_SOURCES
	src/Board.hpp
	src/Command.hpp
	src/Coordinate.hpp
	src/EventHandler.hpp
	src/GameConstants.hpp
	src/Mechanics.hpp
	src/Tetromino.hpp
)

add_library(TetrisCoreLibrary STATIC
	${CORE_HEADERS}
	${CORE_SOURCES}
)

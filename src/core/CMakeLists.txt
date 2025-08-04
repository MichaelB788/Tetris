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
	src/Board.cpp
	src/Command.cpp
	
	src/EventHandler.cpp
	src/Mechanics.cpp
	src/Tetromino.cpp
)

add_library(TetrisCoreLibrary STATIC
	${CORE_HEADERS}
	${CORE_SOURCES}
)

target_include_directories(TetrisCoreLibrary PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include/TetrisCoreLibrary>
)

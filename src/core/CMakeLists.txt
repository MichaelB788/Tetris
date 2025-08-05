set(CORE_HEADERS
	include/Command.hpp
	include/EventHandler.hpp
	include/Flat2DArray.hpp
	include/GameConstants.hpp
	include/Mechanics.hpp
	include/Playfield.hpp
	include/Tetromino.hpp
	include/Vector2.hpp
)

set(CORE_SOURCES
	src/Command.cpp
	src/EventHandler.cpp
	src/Mechanics.cpp
	src/Playfield.cpp
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

# TODO: Finish up with the core components and add them back to this CMake.
set(CORE_HEADERS
	include/Flat2DArray.hpp
	include/GameConstants.hpp
	include/Playfield.hpp
	include/Vector2.hpp
)

set(CORE_SOURCES
	src/Playfield.cpp
)

add_library(TetrisCoreLibrary STATIC
	${CORE_HEADERS}
	${CORE_SOURCES}
)

target_include_directories(TetrisCoreLibrary PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/TetrisCoreLibrary>
)

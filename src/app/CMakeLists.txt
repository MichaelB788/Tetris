set(MAIN_SOURCES
	Game/Tetris.cpp
	Game/Tetris.hpp
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp ${MAIN_SOURCES})

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
	SDL2::SDL2
	SDL2_ttf::SDL2_ttf
)

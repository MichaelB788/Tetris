add_library(TetrisAppLibrary
	Game/Tetris.cpp
)

target_include_directories(TetrisAppLibrary PUBLIC Game)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC 
	SDL2::SDL2
	SDL2::SDL2main
	SDL2_ttf::SDL2_ttf
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE TetrisAppLibrary)
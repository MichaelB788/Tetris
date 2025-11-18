add_library(tetris_app
	tetris.cpp
)
add_library(Tetris::App ALIAS tetris_app)

set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  Tetris::App
  Tetris::Core
	Tetris::Renderer
)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
	SDL2::SDL2
	SDL2::SDL2main
	SDL2_ttf::SDL2_ttf
)

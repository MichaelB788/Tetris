add_library(tetris_src
        EventHandler.cpp
        main.cpp
        mechanics.cpp
        Matrix.cpp
        NextQueue.cpp
        TetrisApp.cpp
        Tetris.cpp
        Clock.cpp
        Tetromino.cpp
        TetrisRenderer.cpp
        SDLRendererBackend.cpp
        SDLWindowBackend.cpp
        SDLPlatform.cpp
)

set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_executable(${EXECUTABLE_NAME} main.cpp)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        SDL3::SDL3
        tetris_src
)

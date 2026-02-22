add_library(tetris_src
        BoardRenderer.cpp
        Clock.cpp
        EventHandler.cpp
        HUDRenderer.cpp
        main.cpp
        mechanics.cpp
        Matrix.cpp
        NextQueue.cpp
        pixel.cpp
        TetrisApp.cpp
        Tetris.cpp
        Tetromino.cpp
        TextRenderer.cpp
        PlatformSDL.cpp
)

set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_executable(${EXECUTABLE_NAME} main.cpp)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        tetris_src
)

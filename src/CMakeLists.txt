add_library(GameLibrary SHARED
    API/GameCore.cpp 

    Game/Objects/Coordinate.cpp
    Game/Objects/Grid.cpp
    Game/Objects/Piece.cpp
    Game/Objects/Mechanics.cpp
    Game/Tetris.cpp

    Components/Graphics.cpp
    Components/EventHandler.cpp
)

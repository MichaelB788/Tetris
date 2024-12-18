add_library(GameLibrary SHARED
    API/GameCore.cpp 

    Components/Graphics.cpp
    Components/EventHandler.cpp
    Components/Commands/Move.cpp

    Game/Objects/Coordinate.cpp
    Game/Objects/Grid.cpp
    Game/Objects/Piece.cpp
    Game/Objects/Mechanics.cpp
    Game/Tetris.cpp
)

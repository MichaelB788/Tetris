add_library(GameLibrary SHARED
    api/SDL-Subsystems.cpp 

    Components/Graphics.cpp
    Components/Draw.cpp

    Components/EventHandler.cpp
    Components/Commands/Move.cpp
    Components/Commands/Rotate.cpp
    Components/Commands/Drop.cpp
    Components/Commands/Store.cpp

    Game/Objects/Coordinate.cpp
    Game/Objects/Grid.cpp
    Game/Objects/Piece.cpp
    Game/Mechanics.cpp
    Game/Tetris.cpp
)

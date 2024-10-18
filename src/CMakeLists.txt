add_library(GameLibrary SHARED
    API/SDLUtils.cpp 

    Game/Objects/Coordinate.cpp
    Game/Objects/Piece.cpp
    Game/Objects/PieceManager.cpp
    Game/Tetris.cpp

    Components/Graphics.cpp
    Components/EventHandler.cpp
)

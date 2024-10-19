add_library(GameLibrary SHARED
    API/GameCore.cpp 

    Game/Objects/Coordinate.cpp
    Game/Objects/Board.cpp
    Game/Objects/Piece.cpp
    Game/Objects/PieceManager.cpp
    Game/Tetris.cpp

    Components/Graphics.cpp
    Components/EventHandler.cpp
)

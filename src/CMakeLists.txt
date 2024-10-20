add_library(GameLibrary SHARED
    API/GameCore.cpp 

    Game/Objects/Coordinate.cpp
    Game/Objects/TetrisBoard.cpp
    Game/Objects/PieceManager.cpp
    Game/Tetris.cpp

    Components/Graphics.cpp
    Components/EventHandler.cpp
)

add_library(GameLibrary SHARED
    SDL/Render.cpp
    SDL/Window.cpp

    # Game/Piece.cpp
    Game/Board.cpp

    Components/Draw.cpp
    Components/EventHandler.cpp
)

add_library(GameLibrary SHARED
    api/sdl/Window.cpp 
    api/sdl/Renderer.cpp 
    api/sdl/Font.cpp 

    api/Core.cpp 

    Components/Visual/Graphics.cpp
    Components/Visual/Draw.cpp

    Components/Event/EventHandler.cpp
    Components/Event/Commands/Move.cpp
    Components/Event/Commands/Rotate.cpp
    Components/Event/Commands/Drop.cpp
    Components/Event/Commands/Store.cpp

    Components/Context.cpp

    Game/Objects/Coordinate.cpp
    Game/Objects/Grid.cpp
    Game/Objects/Piece.cpp
    Game/Mechanics.cpp
    Game/Tetris.cpp
)

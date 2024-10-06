add_library(GameLibrary SHARED
    SDL/Render.cpp
    SDL/Window.cpp

    Game/Block.cpp
    Game/CoordinatePoint.cpp

    Components/Draw.cpp
    Components/EventHandler.cpp
)

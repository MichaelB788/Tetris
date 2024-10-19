#include <SDL2/SDL.h>

#include "Game/Tetris.hpp"
#include "API/GameCore.hpp"
#include "Components/Graphics.hpp"

int main (int argc, char **argv)
{
    GameCore core;

    GraphicsModule graphics = GraphicsModule(core.m_Renderer);

    Tetris tetris;

    tetris.runGame(graphics);

    core.terminate();

    SDL_Quit();

    return 0;
}

#include <SDL2/SDL.h>
#include <assert.h>

#include "Game/Tetris.hpp"
#include "API/GameCore.hpp"
#include "Components/Graphics.hpp"

int main (int argc, char **argv)
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);

    GameCore core;

    GraphicsModule graphics = GraphicsModule(core.m_Renderer);

    Tetris tetris;

    tetris.runGame(graphics);

    return 0;
}

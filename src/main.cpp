#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

#include "Game/Tetris.hpp"

int main (int argc, char **argv)
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0 &&
           TTF_Init() == 0);

    Tetris tetris;

    return 0;
}

#include <SDL2/SDL.h>
#include <assert.h>

#include "Game/Tetris.hpp"

int main (int argc, char **argv)
{
    // It is crucial to use an SDL function in main;
    // CMake may fail to link SDL2 during compilation otherwise.
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);

    Tetris tetris;

    return 0;
}

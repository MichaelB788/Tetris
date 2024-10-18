#include <SDL2/SDL.h>

#include "Game/Tetris.hpp"

int main (int argc, char **argv)
{
    new Tetris();
    SDL_Quit();
    return 0;
}

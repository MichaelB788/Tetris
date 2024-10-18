#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>

typedef class Tetris
{
    bool gameIsRunning;

    SDL_Event event;

    char piecetypes[7] = {'I','O','T','S','Z','L','J'};

    void clearBoard();

public:
    Tetris();
    
} Tetris;

#endif

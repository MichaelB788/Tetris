#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "Player.hpp"

typedef class Tetris
{
private:
    bool m_running = true;
     
    Player m_player;

    SDL_Event m_event;

    void updateGame();

public:
    Tetris();

} Tetris;

#endif

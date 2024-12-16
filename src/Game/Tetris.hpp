#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "Player.hpp"

typedef class Tetris
{
private:
    enum Difficulty 
    {
        EASY = 300,
        NORMAL = 200,
        HARD = 100 
    }; 

    Player m_player;

    SDL_Event m_event;
    
    Difficulty m_difficulty = EASY;

    unsigned int m_timer = 0;

    unsigned int m_points = 0;

    bool m_running = true;

    void invokeGravity();

    void updateGame();

public:
    Tetris();

} Tetris;

#endif

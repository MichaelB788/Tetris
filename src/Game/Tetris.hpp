#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include "../Components/Graphics.hpp"
#include "Player.hpp"

typedef class Tetris
{
private:
    bool m_gameIsRunning = true;
     
    Player m_player;

    void updateGame();

public:
    Tetris() = default;

    void runGame(GraphicsModule gm);
} Tetris;

#endif

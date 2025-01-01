#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>

#include "../api/Core.hpp"
#include "../Components/Context.hpp"
#include "Objects/Piece.hpp"

typedef class Tetris
{
private:
    // Members 
    Core m_core;

    Context m_context;

    SDL_Event m_event;

    unsigned int m_timer = 0, m_points = 0;

    Difficulty m_difficulty = EASY;

    Piece m_piece;

    // Functions
    void updateGame();

public:
    Tetris();
} Tetris;

#endif

#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include "../../Game/Variables.hpp"
#include "../../Game/Objects/Piece.hpp"
#include "Text.hpp"

namespace Draw
{
    unsigned int const TILE_SIZE = 40;

    void setColor(Tile id, SDL_Renderer* p_renderer);

    void board(SDL_Renderer* p_renderer);

    void tile(int x, int y, Tile id, SDL_Renderer* p_renderer);

    void nextAndStored(Piece& piece, SDL_Renderer* p_renderer);

    void text(Text& text, int x, int y);
};

#endif

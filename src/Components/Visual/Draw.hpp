#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include "../../Game/Variables.hpp"
#include "../../Game/Objects/Piece.hpp"

namespace Draw
{
    unsigned int const tileSize = 40;

    void setColor(Tile id, SDL_Renderer* p_renderer);

    void board(SDL_Renderer* p_renderer);

    void tile(int x, int y, Tile id, SDL_Renderer* p_renderer);

    void nextAndStored(Piece& piece, SDL_Renderer* p_renderer);

    void text(int x, int y, SDL_Texture* text);
};

#endif

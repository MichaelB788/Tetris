#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <SDL2/SDL.h>
#include "../Game/Piece.cpp"

namespace Draw 
{
    void setColor(char id, SDL_Renderer* ren);
    void drawBoard(std::vector<std::vector<char>> board, SDL_Renderer* ren);
    void drawTile(int x, int y, char id, SDL_Renderer* ren);
}

#endif

#include <SDL2/SDL.h>
#include <array>

#include "Graphics.hpp"

#define TILE_SIZE 40

void Graphics::setColor(char id, SDL_Renderer* ren)
{
    switch (id)
    {
        case 'I':
            SDL_SetRenderDrawColor(ren, 0, 255, 255, 1);
            break;
        case 'O':
            SDL_SetRenderDrawColor(ren, 255, 255, 0, 1);
            break;
        case 'T':
            SDL_SetRenderDrawColor(ren, 255, 0, 255, 1);
            break;
        case 'S':
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 1);
            break;
        case 'Z':
            SDL_SetRenderDrawColor(ren, 0, 255, 0, 1);
            break;
        case 'L':
            SDL_SetRenderDrawColor(ren, 0, 0, 255, 1);
            break;
        case 'J':
            SDL_SetRenderDrawColor(ren, 255, 145, 0, 1);
            break;
        case '#':
            SDL_SetRenderDrawColor(ren, 0, 0, 250, 0);
            break;
        default:
            break;
    }
}

void Graphics::renderFrame(std::array<std::array<char, 10>, 20> &board, SDL_Renderer* ren)
{
    int y_pos = 0;

    for (auto row : board)
    {
        int x_pos = 0;
        for (auto col : row)
        { 
            x_pos++;
            renderTile(x_pos, y_pos, col, ren);
        }
        y_pos++;
    }
}

void Graphics::renderTile(int x, int y, char id, SDL_Renderer* ren)
{
    SDL_Rect tile;
    tile.x = TILE_SIZE * x;
    tile.y = TILE_SIZE * y;
    tile.h = TILE_SIZE;
    tile.w = TILE_SIZE;

    setColor(id, ren);
    (id == '#')? SDL_RenderDrawRect(ren, &tile) : SDL_RenderFillRect(ren, &tile);
} 

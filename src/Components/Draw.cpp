#include <SDL2/SDL.h>
#include <stdexcept>
#include <vector>

#include "../Game/Piece.hpp"
#include "Draw.hpp"

# define TILE_SIZE 40

void Draw::setColor(char id, SDL_Renderer* ren)
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
        case '|':
        case '_':
            SDL_SetRenderDrawColor(ren, 125, 225, 255, 1);
            break;
        default:
            throw std::invalid_argument("Invalid character given to Draw::drawColor()");
    }
}

void Draw::drawBoard(std::vector<std::vector<char>> board, SDL_Renderer* ren)
{
    int y_pos = 0;

    for (auto y : board)
    {
        int x_pos = 0;
        for (auto x : y)
        { 
            x_pos++;
            drawTile(x_pos, y_pos, x, ren);
        }
        y_pos++;
    }
}

void Draw::drawTile(int x, int y, char id, SDL_Renderer* ren)
{
    // Our tile specs
    SDL_Rect tile;

    tile.x = TILE_SIZE * x;
    tile.y = TILE_SIZE * y;
    tile.h = TILE_SIZE;
    tile.w = TILE_SIZE;

    // Set the color based on the character on the current tile
    setColor(id, ren);

    (id == '#' || id == '|' || id == '_')?
        SDL_RenderDrawRect(ren, &tile) : SDL_RenderFillRect(ren, &tile);
} 

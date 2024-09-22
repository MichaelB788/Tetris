#include <SDL2/SDL.h>
#include <stdexcept>

#include "../Game/Block.h"
#include "Draw.h"

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
        default:
            throw std::invalid_argument("Invalid Block type: Could not set drawing color.");
    }
}

void Draw::block(Block bl, SDL_Renderer* ren)
{
    // Create a tile at each coordinate point in the Block, 
    // then draw it on the screen.
    setColor(bl.getID(), ren);

    for (CoordinatePoint cp : bl.getBlock())
    {
        SDL_Rect tile;
        tile.h = 20;
        tile.w = 20;
        tile.x = cp.getX();
        tile.y = cp.getY();

        // Draw the tile
        SDL_RenderFillRect(ren, &tile);
    }

    SDL_RenderPresent(ren);
}

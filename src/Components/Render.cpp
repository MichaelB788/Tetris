#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Render.h"
#include "../Game/CoordinatePoint.h"
#include "../Game/Block.h"

SDL_Renderer* Render::createRenderer(SDL_Window* win)
{
    return SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

bool Render::isNull(SDL_Renderer* ren)
{
    if (ren == NULL) 
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl; 

    return ren == NULL;
}

void Render::setDrawColor(char id, SDL_Renderer* ren)
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

void Render::drawBlock(Block bl, SDL_Renderer* ren)
{
    // Create a tile at each coordinate point in the Block, 
    // then draw it on the screen.
    setDrawColor(bl.getID(), ren);

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

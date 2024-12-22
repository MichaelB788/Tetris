#include <SDL2/SDL.h>

#include "Graphics.hpp"
#include "../Game/Objects/Grid.hpp"

GraphicsModule::GraphicsModule(SDL_Renderer* ren)
{
    p_renderer = ren;
}

GraphicsModule::~GraphicsModule()
{
    p_renderer = nullptr;
}

void GraphicsModule::setColor(char id)
{
    switch (id)
    {
        case 'I':
        case 'i':
            SDL_SetRenderDrawColor(p_renderer, 0, 255, 255, 1);
            break;
        case 'O':
        case 'o':
            SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 1);
            break;
        case 'T':
        case 't':
            SDL_SetRenderDrawColor(p_renderer, 255, 0, 255, 1);
            break;
        case 'S':
        case 's':
            SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 1);
            break;
        case 'Z':
        case 'z':
            SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
            break;
        case 'L':
        case 'l':
            SDL_SetRenderDrawColor(p_renderer, 255, 145, 0, 1);
            break;
        case 'J':
        case 'j':
            SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, 1);
            break;
        default:
            break;
    }
}

void GraphicsModule::drawBoard()
{
    // Draws every tile on the grid except for the surrounding border.
    for (int row = 1; row < 21; row++)
        for (int col = 1; col < 11; col++)
            drawTile(col - 1, row - 1,
                     Grid::tileAt(col, row));
}

void GraphicsModule::drawTile(int x, int y, char id)
{
    SDL_Rect tile;
    tile.x = tileSize * x;
    tile.y = tileSize * y;
    tile.h = tileSize;
    tile.w = tileSize;

    if (id == '#')
    {
        SDL_SetRenderDrawColor(p_renderer, 0, 0, 150, 0);
        SDL_RenderDrawRect(p_renderer, &tile);
    } 
    else 
    {
        setColor(id);
        SDL_RenderFillRect(p_renderer, &tile);

        SDL_SetRenderDrawColor(p_renderer, 0, 0, 150, 0);
        SDL_RenderDrawRect(p_renderer, &tile);
    } 
} 

void GraphicsModule::clearAndPresentFrame()
{
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);

    SDL_RenderClear(p_renderer);

    drawBoard();

    SDL_RenderPresent(p_renderer); 
}

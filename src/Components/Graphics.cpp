#include <SDL2/SDL.h>

#include "Graphics.hpp"

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
            SDL_SetRenderDrawColor(p_renderer, 0, 255, 255, 1);
            break;
        case 'O':
            SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 1);
            break;
        case 'T':
            SDL_SetRenderDrawColor(p_renderer, 255, 0, 255, 1);
            break;
        case 'S':
            SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
            break;
        case 'Z':
            SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 1);
            break;
        case 'L':
            SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, 1);
            break;
        case 'J':
            SDL_SetRenderDrawColor(p_renderer, 255, 145, 0, 1);
            break;
        case '#':
            SDL_SetRenderDrawColor(p_renderer, 250, 250, 250, 0);
            break;
        default:
            break;
    }
}

void GraphicsModule::drawBoard(Board board)
{
    // Board has dimenstions 20 x 10
    for (int row = 0; row < 20; row++)
        for (int col = 0; col < 10; col++)
            drawTile(col, row, board.at(row, col));
}

void GraphicsModule::drawTile(int x, int y, char id)
{
    SDL_Rect tile;
    tile.x = tileSize * x;
    tile.y = tileSize * y;
    tile.h = tileSize;
    tile.w = tileSize;

    setColor(id);

    (id == '#') ? SDL_RenderDrawRect(p_renderer, &tile) : SDL_RenderFillRect(p_renderer, &tile);
} 

void GraphicsModule::clearAndPresentFrame(Board board)
{
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);

    SDL_RenderClear(p_renderer);

    drawBoard(board);

    SDL_RenderPresent(p_renderer); 
}

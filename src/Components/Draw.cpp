#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "Draw.hpp"
#include "../Game/Mechanics.hpp"
#include "../Game/Objects/Grid.hpp"

void Draw::setColor(Tile id, SDL_Renderer* p_renderer)
{
    switch (id)
    {
        case I: case i:
            SDL_SetRenderDrawColor(p_renderer, 0, 255, 255, 1);
            break;
        case O: case o:
            SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 1);
            break;
        case T: case t:
            SDL_SetRenderDrawColor(p_renderer, 255, 0, 255, 1);
            break;
        case S: case s:
            SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 1);
            break;
        case Z: case z:
            SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
            break;
        case L: case l:
            SDL_SetRenderDrawColor(p_renderer, 255, 145, 0, 1);
            break;
        case J: case j:
            SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, 1);
            break;
        default:
            break;
    }
}

void Draw::board(SDL_Renderer* p_renderer)
{
    // row and col set to 1 to skip drawing the walls
    for (int row = 1; row < 21; row++)
        for (int col = 1; col < 11; col++)
            // Draw the board starting at the top left
            // corner of the screen.
            Draw::tile(col - 1, row - 1,
                       Grid::tileAt(col, row),
                       p_renderer);
}

void Draw::tile(int x, int y, Tile id, SDL_Renderer* p_renderer)
{
    SDL_Rect tile;
    tile.x = tileSize * x, tile.y = tileSize * y;
    tile.h = tileSize, tile.w = tileSize;

    // Fill the tile if it is a piece.
    if (id < 14)
    {
        setColor(id, p_renderer);
        SDL_RenderFillRect(p_renderer, &tile);
    } 

    // Draw a rectangle around all tiles
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 150, 0);
    SDL_RenderDrawRect(p_renderer, &tile);
} 

void Draw::nextAndStored(Piece& piece, SDL_Renderer* p_renderer)
{
    const unsigned int 
        X_POS = 9,
        Y_POS_NEXT_PIECE = 5,
        Y_POS_STORED_PIECE = 10;

    Tile
        next = piece.next(),
        stored = piece.stored();

    for (Point& point : Mechanics::giveNewPiece(next))
    {
        Draw::tile(X_POS + point.getX(),
                   Y_POS_NEXT_PIECE + point.getY(),
                   next,
                   p_renderer);
    }

    if (stored != NIL)
        for (Point& point : Mechanics::giveNewPiece(stored))
        {
            Draw::tile(X_POS + point.getX(),
                       Y_POS_STORED_PIECE + point.getY(),
                       stored,
                       p_renderer);
        }
}

void Draw::text(int x, int y, SDL_Texture* text)
{
}

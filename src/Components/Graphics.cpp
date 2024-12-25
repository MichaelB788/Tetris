#include <SDL2/SDL.h>

#include "Graphics.hpp"
#include "../API/Screen.hpp"
#include "../Game/Objects/Grid.hpp"
#include "../Game/Objects/Mechanics.hpp"

void GraphicsModule::clearAndPresentFrame()
{
    // Clear
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_renderer);

    // Draw
    drawBoard();
    drawStats();

    // Present
    SDL_RenderPresent(p_renderer); 
}

void GraphicsModule::setColor(Tile id)
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

void GraphicsModule::drawBoard()
{
    // row and col set to 1 to skip drawing the walls
    for (int row = 1; row < 21; row++)
        for (int col = 1; col < 11; col++)
            // Draw the board starting at the top left
            // corner of the screen.
            drawTile(col - 1,
                     row - 1,
                     Grid::tileAt(col, row));
}

void GraphicsModule::drawTile(int x, int y, Tile id)
{
    SDL_Rect tile;
    tile.x = tileSize * x, tile.y = tileSize * y;
    tile.h = tileSize, tile.w = tileSize;

    // Fill the tile if it is a piece.
    if (id < 14)
    {
        setColor(id);
        SDL_RenderFillRect(p_renderer, &tile);
    } 

    // Draw a rectangle around all tiles
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 150, 0);
    SDL_RenderDrawRect(p_renderer, &tile);
} 

void GraphicsModule::drawStats()
{
    Tile next = p_piece->next(), stored = p_piece->stored();

    for (Point& point :
         Mechanics::giveNewPiece(next))
            drawTile(NEXT_PIECE_X + point.getX(),
                     NEXT_PIECE_Y + point.getY(),
                     next);

    if (stored != NIL)
        for (Point& point :
        Mechanics::giveNewPiece(stored))
            drawTile(STORED_PIECE_X + point.getX(),
                     STORED_PIECE_Y + point.getY(),
                     stored);
}

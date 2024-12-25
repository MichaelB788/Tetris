#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "../Game/Tile.hpp"
#include "../Game/Objects/Piece.hpp"

/* Handles the visuals.
 *
 * Draws the board to the left and game stats to
 * the right of the window. 
 * */
struct GraphicsModule
{
    // Constructor
    GraphicsModule(SDL_Renderer* ren,
                   Piece* piece) :
    p_renderer(ren),
    p_piece(piece) {};

    // Method
    void clearAndPresentFrame();

private:
    // Members
    unsigned int const tileSize = 40;

    SDL_Renderer* p_renderer;

    Piece* p_piece;

    // Methods
    void setColor(Tile id);

    void drawBoard();

    void drawTile(int x, int y, Tile id);

    void drawStats();
};

#endif

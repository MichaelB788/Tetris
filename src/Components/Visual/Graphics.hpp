#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "../../Game/Objects/Piece.hpp"

/* Handles the visuals.
 *
 * Draws the board to the left and game stats to
 * the right of the window. 
 * */
struct Graphics
{
    // Constructor
    Graphics(SDL_Renderer* ren, Piece& piece) :
        p_renderer(ren),
        m_piece(piece) {};

    // Method
    void clearAndPresentFrame();

private:
    // Members
    unsigned int const tileSize = 40;

    SDL_Renderer* p_renderer;
        
    Piece& m_piece;
};

#endif

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "../Game/Objects/Piece.hpp"
#include "../api/sdl/Renderer.hpp"

/* Handles the visuals.
 *
 * Draws the board to the left and game stats to
 * the right of the window. 
 * */
struct Graphics
{
    // Constructor
    Graphics(Renderer& ren, Piece& piece) :
        p_renderer(ren.get()),
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

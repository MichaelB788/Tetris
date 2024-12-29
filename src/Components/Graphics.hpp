#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "../Game/Objects/Piece.hpp"
#include <SDL2/SDL_ttf.h>

/* Handles the visuals.
 *
 * Draws the board to the left and game stats to
 * the right of the window. 
 * */
struct Graphics
{
    // Constructor
    Graphics(SDL_Renderer* ren,
             TTF_Font* font,
             Piece& piece) :
    p_renderer(ren),
    p_font(font),
    m_piece(piece) {};

    // Method
    void clearAndPresentFrame();

private:
    // Members
    unsigned int const tileSize = 40;

    SDL_Renderer* p_renderer;
        
    TTF_Font* p_font;

    Piece& m_piece;
};

#endif

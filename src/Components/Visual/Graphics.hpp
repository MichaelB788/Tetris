#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "../../Game/Objects/Piece.hpp"
#include "Text.hpp"

/* Handles the visuals.
 *
 * Draws the board to the left and game stats to
 * the right of the window. 
 * */
struct Graphics
{
    // Constructor
    Graphics(SDL_Renderer* ren, TTF_Font* font,
             Piece& piece, unsigned int points);

    // Method
    void clearAndPresentFrame();

private:
    // Members
    SDL_Renderer* m_renderer;

    SDL_Color m_textColor = { 255, 255, 255, 255 };

    Text m_points;

    Text m_nextmsg;

    Text m_storedmsg;
        
    Piece& m_piece;
};

#endif

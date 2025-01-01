#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Graphics.hpp"
#include "Draw.hpp"

Graphics::Graphics(SDL_Renderer* ren, TTF_Font* font,
                   Piece& piece, unsigned int points) :
    m_renderer(ren), m_piece(piece),
    m_points(ren, font, points, m_textColor),
    m_nextmsg(ren, font, "Next Piece", m_textColor),
    m_storedmsg(ren, font, "Stored Piece", m_textColor)
{
}

void Graphics::clearAndPresentFrame()
{
    // Clear
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);

    // Draw
    Draw::board(m_renderer);

    Draw::nextAndStored(m_piece, m_renderer);

    Draw::text(m_nextmsg, 13, 0);

    Draw::text(m_storedmsg, 13, 7);

    // Present
    SDL_RenderPresent(m_renderer); 
}

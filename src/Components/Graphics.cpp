#include <SDL2/SDL.h>

#include "Graphics.hpp"
#include "Draw.hpp"

void Graphics::clearAndPresentFrame()
{
    // Clear
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_renderer);

    // Draw
    Draw::board(p_renderer);
    Draw::nextAndStored(m_piece, p_renderer);

    // Present
    SDL_RenderPresent(p_renderer); 
}

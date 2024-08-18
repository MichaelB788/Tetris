#include <SDL2/SDL.h>
#include <iostream>

#include "Render.h"

char tetromino[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};

SDL_Renderer* Render::createRenderer(SDL_Window* win)
{
    return SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

bool Render::isNull(SDL_Renderer* ren)
{
    if (ren == NULL) 
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl; 

    return ren == NULL;
}

void Render::drawTetromino(SDL_Renderer* ren, char tetromino, int x, int y)
{
    // Clear the current rendering target with the drawing color.
    SDL_RenderClear(ren);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 20;
    rect.h = 20;

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); 
    SDL_RenderFillRect(ren, &rect);

    // reset
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

    // present
    SDL_RenderPresent(ren);
}

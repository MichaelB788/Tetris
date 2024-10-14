#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <array>
#include <SDL2/SDL.h>

namespace Graphics 
{
    void setColor(char id, SDL_Renderer* ren);

    void renderFrame(std::array<std::array<char, 10>, 20> &board, SDL_Renderer* ren);

    void renderTile(int x, int y, char id, SDL_Renderer* ren);
}

#endif

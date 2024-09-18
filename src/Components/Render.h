#ifndef SDL_RENDERER
#define SDL_RENDERER

#include "../Game/Block.h"

namespace Render
{
    SDL_Renderer* createRenderer(SDL_Window * win);

    bool isNull(SDL_Renderer* ren);

    void setDrawColor(char id, SDL_Renderer* ren);

    void drawBlock(Block bl, SDL_Renderer* ren);
}

#endif

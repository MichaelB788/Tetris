#ifndef RENDER_H
#define RENDER_H

namespace Render
{
    SDL_Renderer* createRenderer(SDL_Window * win);

    bool isNull(SDL_Renderer* ren);
}

#endif

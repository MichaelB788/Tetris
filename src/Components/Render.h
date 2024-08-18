#ifndef SDL_RENDERER
#define SDL_RENDERER

namespace Render
{
    SDL_Renderer* createRenderer(SDL_Window * win);

    bool isNull(SDL_Renderer* ren);

    void drawTetromino(SDL_Renderer* ren, int x, int y);
}

#endif

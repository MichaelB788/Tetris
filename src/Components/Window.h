#ifndef SDL_WINDOW
#define SDL_WINDOW

namespace Window
{
    SDL_Window* createWindow();

    bool isNull(SDL_Window* win);
}

#endif

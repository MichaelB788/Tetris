#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class WindowObject
{
    public:
    SDL_Window* pSDL_Window = NULL;
    WindowObject();
    ~WindowObject();
};

#endif

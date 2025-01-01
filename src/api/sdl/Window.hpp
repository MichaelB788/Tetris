#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

struct Window
{
    Window(const char *title, int x, int y, int w,
           int h, Uint32 flags);

    ~Window();

    SDL_Window* get(){ return win; }

private: 
    SDL_Window* win;
};

#endif 

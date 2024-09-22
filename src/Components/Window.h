#ifndef WINDOW_H
#define WINDOW_H

namespace Window
{
    SDL_Window* createWindow();

    bool isNull(SDL_Window* win);
}

#endif

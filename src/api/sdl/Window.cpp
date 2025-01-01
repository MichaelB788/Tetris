#include "Window.hpp"
#include <iostream>

Window::Window(const char *title, int x, int y, int w, 
               int h, Uint32 flags)
{
    win = SDL_CreateWindow(title, x, y, w, h, flags); 

    if ( !win )
    {
        std::cout << "Failed to load window: " <<
            SDL_GetError() << std::endl;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(win);
}

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

struct Renderer
{
    Renderer(SDL_Window* window, int index, Uint32 flags);

    ~Renderer();

    SDL_Renderer* get(){ return ren; }

    private: 
    SDL_Renderer* ren;
};

#endif 

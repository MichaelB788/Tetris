#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Font
{
    Font(const char *file, int ptsize);

    ~Font();

    TTF_Font* get(){ return font; }

    private: 
    TTF_Font* font;
};

#endif 

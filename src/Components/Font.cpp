#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace ttf_font
{
    void init()
    {
        TTF_Font* font = TTF_OpenFont("Sans.ttf", 10);
    }

    void close()
    {
        TTF_CloseFont(font);
    }
}


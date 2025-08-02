#include "Font.hpp"
#include <iostream>

Font::Font(const char *file, int ptsize)
{
    font = TTF_OpenFont(file, ptsize); 

    if ( !font )
    {
        std::cout << "Failed to load font: " <<
            SDL_GetError() << std::endl;
    }
}

Font::~Font()
{
    TTF_CloseFont(font);
}

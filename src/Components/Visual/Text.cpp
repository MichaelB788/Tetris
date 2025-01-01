#include "Text.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

Text::Text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Color fg) :
    m_renderer(ren)
{
    m_textSurface = TTF_RenderUTF8_Solid(font, text, fg);

    if ( !m_textSurface )
    {
        std::cout << "Failed to load surface" <<
            TTF_GetError() << std::endl;
    }
    else
    {
        m_textTexture =
            SDL_CreateTextureFromSurface(m_renderer,
                                         m_textSurface);
    }
    
    SDL_FreeSurface(m_textSurface);
}

Text::Text(SDL_Renderer* ren, TTF_Font* font, unsigned int number, SDL_Color fg) :
    m_renderer(ren)
{
    std::string s = std::to_string(number);

    m_textSurface = TTF_RenderUTF8_Solid(font, s.c_str(), fg);

    if ( !m_textSurface )
    {
        std::cout << "Failed to load surface" <<
            TTF_GetError() << std::endl;
    }
    else
    {
        m_textTexture =
            SDL_CreateTextureFromSurface(m_renderer,
                                         m_textSurface);
    }
    
    SDL_FreeSurface(m_textSurface);
}

Text::~Text()
{
    SDL_DestroyTexture(m_textTexture);
}

void Text::set(unsigned int x, unsigned int y,
               unsigned int w, unsigned int h)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.w = w;
    m_pos.h = h;
}

void Text::renderText()
{
    SDL_RenderCopy(m_renderer, m_textTexture, NULL, &m_pos);
}

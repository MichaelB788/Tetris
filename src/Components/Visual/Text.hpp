#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Text
{
    Text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Color fg);

    Text(SDL_Renderer* ren, TTF_Font* font, unsigned int number, SDL_Color fg);

    ~Text();

    void set(unsigned int x, unsigned int y,
             unsigned int w, unsigned int h);

    void renderText();

private:
    int score = 0;

    SDL_Renderer* m_renderer; 

    SDL_Surface* m_textSurface; 

    SDL_Texture* m_textTexture; 

    SDL_Rect m_pos;
};

#endif 

#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>

class Text {
public:
	Text(const char* textString, SDL_Renderer* renderer);

	~Text();

	void createTextTexture(int x, int y);

private:
	TTF_Font* font;
	SDL_Surface* text;
	SDL_Texture* textTexture;
	SDL_Renderer* renderer;
};

#endif

#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL_ttf.h>
#include "util/renderer.hpp"

class Text {
public:
	Text(const char* textString);

	~Text();

	bool createTextTexture(const Renderer& renderer);

	void render(int x, int y, const Renderer& renderer) const {
		if ( textTexture ) renderer.renderTexture(textTexture, { x, y, text->w, text->h });
	};

private:
	TTF_Font* font;
	SDL_Surface* text;
	SDL_Texture* textTexture;
};

#endif

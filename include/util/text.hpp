#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL_ttf.h>
#include "util/renderer.hpp"

class Text {
public:
	Text(const char* textString);

	~Text();

	void createTextTexture(SDL_Renderer* renderer);
	
	bool isInitialized() const {
		return font != nullptr || text != nullptr || textTexture != nullptr;  
	}

	void render(int x, int y, const Renderer& renderer) const {
		if ( textTexture ) renderer.renderTexture(textTexture, { x, y, text->w, text->h });
	};

private:
	TTF_Font* font = nullptr;
	SDL_Surface* text = nullptr;
	SDL_Texture* textTexture = nullptr;
};

#endif

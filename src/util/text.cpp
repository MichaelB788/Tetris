#include "util/text.hpp"

Text::Text(const char* textString, SDL_Renderer* renderer) : renderer(renderer) {
	if ( TTF_Init() < 0 ) {
		printf("Could not initialize SDL_TTF: %s\n", TTF_GetError());
	}

	font = TTF_OpenFont("../assets/font/SpaceMono-Regular.ttf", 30);
	if ( !font ) {
		printf("Could not load font: %s\n", TTF_GetError());
	}

	SDL_Color white = { 255, 255, 255 };
	text = TTF_RenderText_Solid(font, textString, white);
}

Text::~Text() {
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(text);
}

void Text::createTextTexture(int x, int y) {
	if ( text ) {
		textTexture = SDL_CreateTextureFromSurface(renderer, text);
		SDL_Rect dest = { x, y, text->w, text->h };
		SDL_RenderCopy(renderer, textTexture, &dest, nullptr);
	}
}

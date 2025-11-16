#include "util/text.hpp"

Text::Text(const char* textString) {
	if ( TTF_Init() < 0 ) {
		printf("Could not initialize SDL_TTF: %s\n", TTF_GetError());
	}

	font = TTF_OpenFont("../assets/font/SpaceMono-Regular.ttf", 30);
	if ( !font ) {
		printf("Could not load font: %s\n", TTF_GetError());
	}

	SDL_Color white = { 100, 255, 100 };
	text = TTF_RenderText_Solid(font, textString, white);
}

Text::~Text() {
	if ( text && textTexture ) {
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(text);
	}
}

bool Text::createTextTexture(const Renderer& renderer) {
	if ( text ) {
		textTexture = SDL_CreateTextureFromSurface(renderer.getRenderer(), text);
		if ( textTexture != nullptr ) return true;
	}
	printf("Could not create text texture: %s\n", SDL_GetError());
	return false;
}

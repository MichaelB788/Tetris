#include "util/text.hpp"

Text::Text(const char* textString) {
	if ( TTF_Init() < 0 ) printf("Could not initialize SDL_TTF: %s\n", TTF_GetError());

	font = TTF_OpenFont("../assets/font/SpaceMono-Regular.ttf", 30);
	if ( !font ) printf("Could not load font: %s\n", TTF_GetError());

	text = TTF_RenderText_Solid(font, textString, { 255, 255, 255 });
	if ( !text ) printf("Could not load text surface: %s\n", TTF_GetError());
}

Text::~Text() {
	if ( font ) TTF_CloseFont(font);
	if ( text ) SDL_FreeSurface(text);
	if ( textTexture ) SDL_DestroyTexture(textTexture);
}

void Text::createTextTexture(SDL_Renderer* renderer) {
	if ( text ) {
		textTexture = SDL_CreateTextureFromSurface(renderer, text);
		if ( textTexture != nullptr ) return;
	}
	printf("Could not create text texture: %s\n", SDL_GetError());
}

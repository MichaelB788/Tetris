#include "util/text.hpp"

Text::Text(const char* textString, SDL_Renderer* renderer) {
	font = TTF_OpenFont("../assets/font/SpaceMono-Regular.ttf", 30);
	if ( !font ) printf("Could not load font: %s\n", TTF_GetError());

	if ( font ) text = TTF_RenderText_Solid(font, textString, { 255, 255, 255 });
	if ( !text ) printf("Could not load text surface: %s\n", TTF_GetError());
	
	if ( text ) textTexture = SDL_CreateTextureFromSurface(renderer, text);
	if ( !textTexture ) printf("Could not create text texture: %s\n", SDL_GetError());
}

Text::~Text() {
	if ( font ) TTF_CloseFont(font);
	if ( text ) SDL_FreeSurface(text);
	if ( textTexture ) SDL_DestroyTexture(textTexture);
}

#include "util/renderer.hpp"

Renderer::Renderer(SDL_Window* window) {
	sdlRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED); 
	printf("Failed to load renderer: %s\n", SDL_GetError());
}

void Renderer::clear() const {
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);
}

void Renderer::drawRectangle(const SDL_Rect rect, bool filled) const {
	if ( filled ) {
		SDL_RenderFillRect(sdlRenderer, &rect);
	} else {
		SDL_RenderDrawRect(sdlRenderer, &rect);
	}
}

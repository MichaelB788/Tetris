#include "util/renderer.hpp"
#include <SDL2/SDL_render.h>

Renderer::~Renderer() {
	if (sdlRenderer) {
		SDL_DestroyRenderer(sdlRenderer);
		sdlRenderer = nullptr;
	}
}

bool Renderer::initializeSDLRenderer(SDL_Window* window) {
	bool success = true;
	sdlWindow = window;
	sdlRenderer = SDL_CreateRenderer(
			sdlWindow,
			-1,
			SDL_RENDERER_ACCELERATED
			); 

	if ( !sdlRenderer ) {
		printf("Failed to load renderer: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}


void Renderer::clearFrame() const {
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);
}

void Renderer::updateFrame() const {
	SDL_RenderPresent(sdlRenderer);
}

void Renderer::drawRectangle(Color color, bool filled, int x, int y, int w, int h) const {
	switch (color) {
		case Color::WHITE:
			SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 0);
			break;
		case Color::GRAY:
			SDL_SetRenderDrawColor(sdlRenderer, 100, 100, 100, 0);
			break;
		case Color::BLACK: default:
			SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
			break;
	}

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	if (filled) {
		SDL_RenderFillRect(sdlRenderer, &rect);
	} else {
		SDL_RenderDrawRect(sdlRenderer, &rect);
	}
}

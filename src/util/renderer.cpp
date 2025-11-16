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
	sdlRenderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED
			); 

	if ( !sdlRenderer ) {
		printf("Failed to load renderer: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}


void Renderer::clear() const {
	if ( sdlRenderer ) {
		SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
		SDL_RenderClear(sdlRenderer);
	}
}

void Renderer::setSDLRendererColor(Color color) const {
	if ( sdlRenderer ) {
		switch (color) {
			case Color::CYAN:    // I piece
				SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 255, 0);
				break;
			case Color::YELLOW:  // O piece
				SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 0, 0);
				break;
			case Color::PURPLE:  // T piece
				SDL_SetRenderDrawColor(sdlRenderer, 128, 0, 128, 0);
				break;
			case Color::GREEN:   // S piece
				SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 0, 0);
				break;
			case Color::RED:     // Z piece
				SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 0);
				break;
			case Color::BLUE:    // J piece
				SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 0);
				break;
			case Color::ORANGE:  // L piece
				SDL_SetRenderDrawColor(sdlRenderer, 255, 165, 0, 0);
				break;
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
	}
}

void Renderer::drawRectangle(const SDL_Rect& rect, bool filled) const {
	if ( sdlRenderer ) {
		if ( filled ) {
			SDL_RenderFillRect(sdlRenderer, &rect);
		} else {
			SDL_RenderDrawRect(sdlRenderer, &rect);
		}
	}
}

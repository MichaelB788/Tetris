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
	setSDLRendererColor(color);

	SDL_Rect rect = { x, y, w, h };

	if (filled) {
		SDL_RenderFillRect(sdlRenderer, &rect);
	} else {
		SDL_RenderDrawRect(sdlRenderer, &rect);
	}
}

void Renderer::setSDLRendererColor(Color color) const {
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
		
		// Tetromino colors
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
	}
}

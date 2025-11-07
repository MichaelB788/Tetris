#include "util/renderer.hpp"
#include <SDL2/SDL_render.h>

Renderer::~Renderer()
{
	SDL_DestroyRenderer(p_renderer);
	p_renderer = nullptr;
}

void Renderer::initializeSDLRenderer() {
	p_renderer = SDL_CreateRenderer(
			r_window.p_window,
			-1,
			SDL_RENDERER_ACCELERATED
			); 

	if ( !p_renderer ) {
		printf("Failed to load renderer: %s\n", SDL_GetError());
	}
}


void Renderer::clearFrame() const {
	SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
	SDL_RenderClear(p_renderer);
}

void Renderer::updateFrame() const {
	SDL_RenderPresent(p_renderer);
}

void Renderer::drawRectangle(Color color, bool filled, int x, int y, int w, int h) const {
	if (color == Color::WHITE)
		SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 0);
	else 
		SDL_SetRenderDrawColor(p_renderer, 100, 100, 100, 0);

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	if (filled) {
		SDL_RenderFillRect(p_renderer, &rect);
	} else {
		SDL_RenderDrawRect(p_renderer, &rect);
	}
}

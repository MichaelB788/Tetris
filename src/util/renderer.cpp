#include "util/renderer.hpp"

Renderer::~Renderer()
{
	SDL_DestroyRenderer(p_renderer);
	p_renderer = nullptr;
}

Renderer::Renderer(Window& window) : r_window(window) {
	p_renderer = SDL_CreateRenderer(
			r_window.getSDLWindowPointer(),
			-1,
			SDL_RENDERER_ACCELERATED
			); 

	if ( !p_renderer ) {
		printf("Failed to load renderer: %s\n", SDL_GetError());
	} else {
		SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
	}
}

void Renderer::update() {
}

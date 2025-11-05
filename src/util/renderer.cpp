#include "util/renderer.hpp"
#include <iostream>

Renderer::Renderer(SDL_Window* window) {
	p_sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

	if ( !p_sdlRenderer ) std::cout << "Failed to load renderer: " << SDL_GetError() << std::endl;
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(p_sdlRenderer);
	p_sdlRenderer = nullptr;
}

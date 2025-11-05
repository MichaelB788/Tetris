#include "util/renderer.hpp"
#include <iostream>

Renderer::Renderer(SDL_Window* window)
{
	p_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

	if ( !p_renderer ) std::cout << "Failed to load renderer: " << SDL_GetError() << std::endl;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(p_renderer);
	p_renderer = nullptr;
}

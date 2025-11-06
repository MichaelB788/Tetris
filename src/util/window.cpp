#include "util/window.hpp"

Window::Window(const char* title) {
	p_window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_RESIZABLE
			);

	if (!p_window) {
		printf("Failed to load window: %s\n", SDL_GetError());
	}
}

Window::~Window()
{
	SDL_DestroyWindow(p_window);
	p_window = nullptr;
}

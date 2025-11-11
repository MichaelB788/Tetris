#include "util/window.hpp"

Window::Window(const char* title) {
	sdlWindow = SDL_CreateWindow(title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_RESIZABLE
			);

	if (!sdlWindow) {
		printf("Failed to load window: %s\n", SDL_GetError());
	}
}

Window::~Window()
{
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = nullptr;
}

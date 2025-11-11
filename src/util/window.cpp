#include "util/window.hpp"

bool Window::initializeSDLWindow(const char* title) {
	bool success = true;
	sdlWindow = SDL_CreateWindow(title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_RESIZABLE
			);

	if (!sdlWindow) {
		printf("Failed to load window: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

Window::~Window()
{
	if (sdlWindow) {
		SDL_DestroyWindow(sdlWindow);
		sdlWindow = nullptr;
	}
}

#include "util/window.hpp"

Window::Window(const char* title) : windowSize({ 600, 600 }) {
	sdlWindow = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowSize.w,
		windowSize.h,
		SDL_WINDOW_RESIZABLE
	);
	if ( !sdlWindow ) printf("Failed to load window: %s\n", SDL_GetError());
}

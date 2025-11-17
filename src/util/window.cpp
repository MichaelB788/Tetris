#include "util/window.hpp"

void Window::initializeSDLWindow(const char* title) {
	sdlWindow = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowSize.w,
		windowSize.h,
		SDL_WINDOW_RESIZABLE
	);
	if ( !sdlWindow ) printf("Failed to load window: %s\n", SDL_GetError());
}

Window::~Window() {
	if ( sdlWindow ) {
		SDL_DestroyWindow(sdlWindow);
		sdlWindow = nullptr;
	}
}

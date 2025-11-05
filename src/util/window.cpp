#include "util/window.hpp"
#include <iostream>

Window::Window(const char *title) {
    p_window = SDL_CreateWindow(title,
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				WIDTH,
				HEIGHT,
				SDL_WINDOW_RESIZABLE
		);

	if (!p_window) std::cout << "Failed to load window: " << SDL_GetError() << std::endl;
}

Window::~Window()
{
  SDL_DestroyWindow(p_window);
  p_window = nullptr;
}

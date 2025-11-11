#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>

struct Window {
  static constexpr unsigned int WIDTH = 600, HEIGHT = 600;
	SDL_Window* sdlWindow = nullptr;

	Window(const char* title);
	~Window();
};

#endif

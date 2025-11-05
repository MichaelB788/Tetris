#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>

struct Window {
	SDL_Window* p_window = nullptr;
  static constexpr unsigned int WIDTH = 600, HEIGHT = 600;
	Window(const char* title);
	~Window();
};

#endif

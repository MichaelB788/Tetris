#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>

class Window {
public:
  static constexpr unsigned int WIDTH = 600, HEIGHT = 600;

	Window(const char* title);
	~Window();

	friend class Renderer;

private:
	SDL_Window* p_window = nullptr;
};

#endif

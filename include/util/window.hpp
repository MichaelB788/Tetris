#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include "geometry.hpp"

class Window {
public:
	Window() = default;
	~Window();

	/* *
	 * @brief Initializes the internal SDL_Window with the given name
	 * @return true if the operation was successful, false otherwise
	 * */
	bool initializeSDLWindow(const char* title);

	SDL_Window* getWindow() const { return sdlWindow; }

	Dimensions getWindowSize() const {
		return windowSize;
	}

	void updateWindowSize() {
		SDL_GetWindowSize(sdlWindow, &windowSize.w, &windowSize.h);
	}

private:
	Dimensions windowSize;
	SDL_Window* sdlWindow = nullptr;
};

#endif

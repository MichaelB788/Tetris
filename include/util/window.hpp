#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include "geometry.hpp"

class Window {
public:
	Window(const char* title);

	~Window() {
		if ( sdlWindow ) SDL_DestroyWindow(sdlWindow);
	}

	Window(const Window& other) = delete;

	void operator=(const Window& other) = delete;

	/**
	 * @brief Checks if the internal SDL_Window is null.
	 * @note CALL THIS FUNCTION BEFORE DOING ANYTHING WITH THE WINDOW!
	 */
	bool isInitialized() const { return sdlWindow != nullptr; }

	SDL_Window* getWindow() const { return sdlWindow; }

	Dimension2D getWindowSize() const { return windowSize; }

	void handleWindowEvent(const SDL_Event& event) {
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			SDL_GetWindowSize(sdlWindow, &windowSize.w, &windowSize.h);
	}

private:
	Dimension2D windowSize;
	SDL_Window* sdlWindow = nullptr;
};

#endif

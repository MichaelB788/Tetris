#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include "geometry.hpp"

class Window {
public:
	Window() : windowSize{600, 600} {};
	~Window();

	void initializeSDLWindow(const char* title);

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

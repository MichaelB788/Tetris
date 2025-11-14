#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

class Window {
public:
	/* *
	 * @brief Initializes the internal SDL_Window with the given name
	 * @return true if the operation was successful, false otherwise
	 * */
	bool initializeSDLWindow(const char* title);

	SDL_Window* getWindow() const { return sdlWindow; }

	void getWindowDimensions(int& w, int& h) const {
		w = cachedWidth;
		h = cachedHeight;
	}

	void updateWindowDimensions() {
		SDL_GetWindowSize(sdlWindow, &cachedWidth, &cachedHeight);
	}

	~Window();

private:
	int cachedWidth;
	int cachedHeight;
	SDL_Window* sdlWindow = nullptr;
};

#endif

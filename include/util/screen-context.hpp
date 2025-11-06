#ifndef SCREEN_CONTEXT_H
#define SCREEN_CONTEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class ScreenContext {
public:
	bool initializeSDL();

private:
	SDL_Window* p_window;
	SDL_Renderer* p_renderer;
};

#endif

#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

struct Renderer {
	Renderer(SDL_Window* window);
	~Renderer();
	SDL_Renderer* p_renderer = nullptr;
};

#endif

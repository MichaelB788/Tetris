#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_render.h>
#include "util/window.hpp"

class Renderer {
public:
	Renderer(Window& window);
	~Renderer();
	bool initializeSDLRenderer(SDL_Window* window);
	inline SDL_Renderer* getSDLRendererPointer() const { return p_renderer; }
	void update();

private:
	SDL_Renderer* p_renderer = nullptr;
	Window& r_window;
};

#endif

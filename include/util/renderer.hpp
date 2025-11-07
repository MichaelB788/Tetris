#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include "util/window.hpp"

class Renderer {
public:
	enum class Color {
		WHITE, GRAY
	};

	Renderer(Window& window) : r_window(window) {};
	~Renderer();

	void initializeSDLRenderer();
	void clearFrame() const;
	void updateFrame() const;
	void drawRectangle(Color color, bool filled, int x, int y, int w, int h) const;

private:
	SDL_Renderer* p_renderer = nullptr;
	Window& r_window;
};

#endif

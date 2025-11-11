#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

struct Renderer {
	enum class Color {
		WHITE, GRAY, BLACK
	};

	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Window* sdlWindow = nullptr;

	~Renderer();

	bool initializeSDLRenderer(SDL_Window* window);
	void clearFrame() const;
	void updateFrame() const;
	void drawRectangle(Color color, bool filled, int x, int y, int w, int h) const;
};

#endif

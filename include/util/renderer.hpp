#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

class Renderer {
public:
	enum class Color {
		WHITE, GRAY, BLACK, BLUE, RED, GREEN, CYAN, ORANGE, PURPLE, YELLOW
	};

	~Renderer();

	SDL_Renderer* getRenderer() const { return sdlRenderer; }

	/* *
	 * @brief Initializes the internal SDL_Renderer given an SDL_Window
	 * @return true if the operation was successful, false otherwise
	 * */
	bool initializeSDLRenderer(SDL_Window* window);

	void clearFrame() const;

	void updateFrame() const;

	void drawRectangle(Color color, bool filled, int x, int y, int w, int h) const;

private:
	void setSDLRendererColor(Color color) const;

	SDL_Renderer* sdlRenderer = nullptr;

	SDL_Window* sdlWindow = nullptr;
};

#endif

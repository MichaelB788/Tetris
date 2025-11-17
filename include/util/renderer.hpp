#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

class Renderer {
public:
	enum class Color {
		WHITE, GRAY, BLACK, BLUE, RED, GREEN, CYAN, ORANGE, PURPLE, YELLOW
	};

	Renderer() = default;
	~Renderer();

	Renderer(const Renderer& other) = delete;
	void operator=(const Renderer& other) = delete;

	SDL_Renderer* getRenderer() const { return sdlRenderer; }

	void initializeSDLRenderer(SDL_Window* window);

	bool isInitialized() const { return sdlRenderer != nullptr; }

	void clear() const;

	void present() const {
		if ( sdlRenderer ) SDL_RenderPresent(sdlRenderer);
	}

	void drawRectangle(const SDL_Rect& rect, bool filled) const;

	void setSDLRendererColor(Color color) const;

	void renderTexture(SDL_Texture* texture, const SDL_Rect& dest) const {
		if ( sdlRenderer ) SDL_RenderCopy(sdlRenderer, texture, &dest, nullptr);
	}

private:
	SDL_Renderer* sdlRenderer = nullptr;
};

#endif

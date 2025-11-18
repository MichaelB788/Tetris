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

	explicit Renderer(SDL_Window* window);

	~Renderer();

	Renderer(const Renderer& other) = delete;

	void operator=(const Renderer& other) = delete;

	bool isInitialized() const { return sdlRenderer != nullptr; }

	SDL_Renderer* getRenderer() const { return sdlRenderer; }

	/// @brief Paints the SDL_Window black, effectively clearing it
	void clear() const;

	/// @brief Presents any rendering calls done before this function 
	void present() const {
		if ( sdlRenderer ) SDL_RenderPresent(sdlRenderer);
	}

	/// @brief Renders a rectangle to the screen, filled or unfilled
	void drawRectangle(const SDL_Rect& rect, bool filled) const;

	/// @brief Sets the color for future rendering calls
	void setSDLRendererColor(Color color) const;

	/// @brief Copies the texture and renders it to the screen
	void renderTexture(SDL_Texture* texture, const SDL_Rect& dest) const {
		if ( sdlRenderer ) SDL_RenderCopy(sdlRenderer, texture, nullptr, &dest);
	}

private:
	SDL_Renderer* sdlRenderer = nullptr;
};

#endif

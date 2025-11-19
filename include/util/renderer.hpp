#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>

class Renderer {
public:
	explicit Renderer(SDL_Window* window);

	~Renderer() {
		if ( sdlRenderer ) SDL_DestroyRenderer(sdlRenderer);
	};

	Renderer(const Renderer& other) = delete;

	void operator=(const Renderer& other) = delete;

	/**
	 * @brief Checks if the internal SDL_Renderer is null.
	 * @note CALL THIS FUNCTION BEFORE DOING ANYTHING WITH THE RENDERER!
	 */
	bool isInitialized() const { return sdlRenderer != nullptr; }

	SDL_Renderer* getRenderer() const { return sdlRenderer; }

	/// @brief Paints the SDL_Window black, effectively clearing it
	void clear() const;

	/// @brief Presents any rendering calls done before this function 
	void present() const {
		SDL_RenderPresent(sdlRenderer);
	}

	/// @brief Renders a rectangle to the screen, filled or unfilled
	void drawRectangle(const SDL_Rect rect, bool filled = false) const;

	/// @brief Sets the color for future rendering calls
	void setSDLRendererColor(const SDL_Color color) const {
		SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
	};

	/// @brief Copies the texture and renders it to the screen
	void renderTexture(SDL_Texture* texture, const SDL_Rect& dest) const {
		SDL_RenderCopy(sdlRenderer, texture, nullptr, &dest);
	}

private:
	SDL_Renderer* sdlRenderer = nullptr;
};

#endif

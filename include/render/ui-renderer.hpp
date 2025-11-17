#ifndef RENDER_UI
#define RENDER_UI
#include "util/renderer.hpp"
#include "util/text.hpp"
#include "util/geometry.hpp"

class UIRenderer {
public:
	UIRenderer() : storedText("Stored:"), nextText("Next:") {};

	void createTextTexture(SDL_Renderer* renderer);

	void renderText(const Renderer& renderer, const Dimension2D window) const;

private:
	// BUG: Since these are stack allocated, TTF_Init initializes after these objects.
	Text storedText;
	Text nextText;
};

#endif

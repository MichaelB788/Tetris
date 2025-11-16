#ifndef RENDER_UI
#define RENDER_UI
#include "util/text.hpp"
#include "util/window.hpp"

class UIRenderer {
public:
	UIRenderer(SDL_Renderer* renderer)
		: storedText("Stored", renderer),
			nextText("Next", renderer) 
	{}

	void renderText(Window& window);

private:
	Text storedText;
	Text nextText;
};

#endif

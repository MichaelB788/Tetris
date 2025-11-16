#ifndef RENDER_UI
#define RENDER_UI
#include "util/renderer.hpp"
#include "util/text.hpp"
#include "util/window.hpp"

class UIRenderer {
public:
	UIRenderer(const Renderer& renderer);

	void renderText(const Renderer& renderer, const Window& window);

private:
	Text storedText;
	Text nextText;
};

#endif

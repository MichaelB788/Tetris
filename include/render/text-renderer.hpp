#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H
#include "render/matrix-renderer.hpp"
#include "util/text.hpp"

class TextRenderer {
public:
	TextRenderer(SDL_Renderer* renderer)
		: nextText("Next", renderer),
			storedText("Stored", renderer)
	{
		textHasInit = storedText.isInitialized() && nextText.isInitialized();
	}

	void render(const Renderer& renderer, const int textPosX);

private:
	bool textHasInit = false;

	Text storedText;
	Text nextText;
};

#endif

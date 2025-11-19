#include "render/text-renderer.hpp"

void TextRenderer::render(const Renderer& renderer, const int textPosX) {
	if ( textHasInit ) {
		nextText.render(textPosX, 100, renderer);
		storedText.render(textPosX, 600, renderer);
	}
}

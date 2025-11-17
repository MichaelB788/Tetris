#include "render/ui-renderer.hpp"

void UIRenderer::createTextTexture(SDL_Renderer* renderer) {
	storedText.createTextTexture(renderer);
	nextText.createTextTexture(renderer);
}

void UIRenderer::renderText(const Renderer& renderer, const Dimension2D windowDimension) const {
	if ( storedText.isInitialized() && nextText.isInitialized() ) {
		storedText.render(0, 0, renderer);
		nextText.render(0, 0, renderer);
	}
}

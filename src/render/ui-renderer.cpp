#include "render/ui-renderer.hpp"

UIRenderer::UIRenderer(const Renderer& renderer) : storedText("Stored:"), nextText("Next:") {
	storedText.createTextTexture(renderer);
	nextText.createTextTexture(renderer);
}

void UIRenderer::renderText(const Renderer& renderer, const Window& window) {
	auto [offsetX, offsetY] = window.getWindowSize();

	storedText.render(offsetX, offsetY, renderer);
	nextText.render(offsetX, offsetY, renderer);
}

#include "render/ui-renderer.hpp"

void UIRenderer::renderText(Window& window) {
	int winWidth, winHeight;
	window.getWindowDimensions(winWidth, winHeight);

	int offsetX = 500;
	int offsetY = 500;

	storedText.createTextTexture(offsetX, offsetY);
	nextText.createTextTexture(0, 0);
}

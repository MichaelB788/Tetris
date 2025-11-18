#include "render/ui-renderer.hpp"

void UIRenderer::renderText(const Renderer& renderer, const MatrixRenderer& matrixRenderer) {
	if ( storedText.isInitialized() && nextText.isInitialized() ) {
		offset.x = matrixRenderer.getMatrixEnd();
		storedText.render(offset.x, offset.y, renderer);
		nextText.render(offset.x, offset.y + 200, renderer);
	}
}

void UIRenderer::renderStoredAndNext(const Tetromino& stored, const Tetromino& next) {
	// TODO: Tetromino Renderer
}

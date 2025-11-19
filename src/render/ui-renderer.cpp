#include "render/ui-renderer.hpp"

void UIRenderer::render(const Renderer& renderer, const MatrixRenderer& matrixRenderer) {
	textRenderer.render(renderer, matrixRenderer.getMatrixEnd());
}

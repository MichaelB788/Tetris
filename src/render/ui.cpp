#include "render/ui.hpp"

void UI::render(const Matrix& matrix, const TetrominoQueue& queue, Dimension2D windowSize) {
	uiBox.pos.x = (windowSize.w - uiBox.dim.w) / 2;
	uiBox.pos.y = (windowSize.h - uiBox.dim.h) / 2;

	TetrisRenderer::renderMatrix(matrix, renderer, uiBox.pos);
	renderTetrominoQueue(queue);
	if (!queue.isHoldEmpty()) renderHeldTetromino(queue.getHold());
}

void UI::renderTetrominoQueue(const TetrominoQueue& queue) const {
	using namespace TetrisRenderer;
	Vector2 offset = { uiBox.pos.x + MATRIX_PIXEL_SIZE.w + 100, uiBox.pos.y };

	for (const auto& tet : queue.getNextQueue()) {
		offset.y += 200;
		TetrisRenderer::renderTetromino(tet, renderer, offset);
	}
}

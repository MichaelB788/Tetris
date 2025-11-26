#include "render/ui.hpp"
#include "render/tetris-renderer.hpp"

void UI::render(const GameState& gameState, Dimension2D windowSize) {
	uiBox.pos.x = (windowSize.w - uiBox.dim.w) / 2;
	uiBox.pos.y = (windowSize.h - uiBox.dim.h) / 2;

	TetrisRenderer::renderMatrix(gameState.getMatrix(), renderer, uiBox.pos);
	renderTetrominoQueue(gameState.getQueue());
}

void UI::renderText() const {
//if ( storedText.isInitialized() && nextText.isInitialized() ) {
//	nextText.render(position.x, position.y, renderer);
//	storedText.render(position.x, position.y + 600, renderer);
//}
}

void UI::renderTetrominoQueue(const TetrominoQueue& queue) const {
	// Render stored
	Vector2 offset = {uiBox.pos.x + TetrisRenderer::MATRIX_PIXEL_SIZE.w + 100, uiBox.pos.y * TetrisRenderer::TILE_SIZE};
	if ( !queue.isHoldEmpty() ) TetrisRenderer::renderTetromino(queue.getHold(), renderer, offset);

	// Render next queue
	for (const auto& tet : queue.getNextQueue()) {
		offset.y += 100;
		TetrisRenderer::renderTetromino(tet, renderer, offset);
	}
}

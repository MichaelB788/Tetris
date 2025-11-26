#include "render/ui.hpp"

void UI::render(const GameState& gameState, Dimension2D windowSize) {
	uiBox.pos.x = (windowSize.w - uiBox.dim.w) / 2;
	uiBox.pos.y = (windowSize.h - uiBox.dim.h) / 2;

	TetrisRenderer::renderMatrix(gameState.getMatrix(), renderer, uiBox.pos);
	renderTetrominoQueue(gameState.getQueue());
}

void UI::renderTetrominoQueue(const TetrominoQueue& queue) const {
	// Render stored
	Vector2 offset = {uiBox.pos.x + TetrisRenderer::MATRIX_PIXEL_SIZE.w + 100, uiBox.pos.y + 150};
	renderer.setSDLRendererColor(Color::getColor(Color::ID::WHITE));
	renderer.drawRectangle({offset.x - 80, offset.y - 100, TetrisRenderer::TILE_SIZE * 5, TetrisRenderer::TILE_SIZE * 5});
	if ( !queue.isHoldEmpty() ) TetrisRenderer::renderTetromino(queue.getHold(), renderer, offset);

	// Render next queue
	offset.y += 100;
	renderer.setSDLRendererColor(Color::getColor(Color::ID::WHITE));
	renderer.drawRectangle({offset.x - 80, offset.y + 100, TetrisRenderer::TILE_SIZE * 5, TetrisRenderer::TILE_SIZE * 5});
	for (const auto& tet : queue.getNextQueue()) {
		offset.y += 180;
		TetrisRenderer::renderTetromino(tet, renderer, offset);
	}
}

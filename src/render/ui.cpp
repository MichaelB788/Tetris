#include "render/ui.hpp"
#include "render/tetris-renderer.hpp"

void UI::render(const GameState& gameState, Dimension2D windowSize) {
	offset.x = (windowSize.w - TetrisRenderer::MATRIX_PIXEL_SIZE.w) / (2 * TetrisRenderer::TILE_SIZE);
	offset.y = (windowSize.h - TetrisRenderer::MATRIX_PIXEL_SIZE.h) / (2 * TetrisRenderer::TILE_SIZE);
	renderText(offset);
}

void UI::renderText(const Vector2 position) const {
	if ( storedText.isInitialized() && nextText.isInitialized() ) {
		nextText.render(position.x, position.y, renderer);
		storedText.render(position.x, position.y + 600, renderer);
	}
}

void UI::renderTetromino(const Vector2 position, const Tetromino& next, const Tetromino& stored) const {
	TetrisRenderer::renderTetrominoAt(position, next, renderer);
	Vector2 storedPosition = position;
	storedPosition.y += 600;
	if ( !stored.isNull() ) TetrisRenderer::renderTetrominoAt(storedPosition, stored, renderer);
}

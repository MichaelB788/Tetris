#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrixUsingSDL(const Matrix& matrix, const Renderer& renderer, const Window& window) {
	int winWidth, winHeight;
	window.getWindowDimensions(winWidth, winHeight);

	int offsetX = (winWidth - MATRIX_PIXEL_WIDTH) / (2 * TILE_SIZE);
	int offsetY = (winHeight - MATRIX_PIXEL_HEIGHT) / (2 * TILE_SIZE);

	for (unsigned int y = 2; y < Matrix::HEIGHT; y++) {
		for (unsigned int x = 0; x < Matrix::WIDTH; x++) {
			if (matrix(x, y).state == MatrixTile::State::EMPTY) {
				renderer.drawRectangle( Renderer::Color::GRAY, false, pos(x, offsetX), pos(y, offsetY), TILE_SIZE, TILE_SIZE );
			}
			else if (matrix(x, y).state == MatrixTile::State::ACTIVE || matrix(x, y).state == MatrixTile::State::GROUND) {
				renderer.drawRectangle( getTetrominoColor(matrix(x, y)), true, pos(x, offsetX), pos(y, offsetY), TILE_SIZE, TILE_SIZE );
				renderer.drawRectangle( Renderer::Color::BLACK, false, pos(x, offsetX), pos(y, offsetY), TILE_SIZE, TILE_SIZE );
			}
			else {
				renderer.drawRectangle( Renderer::Color::WHITE, false, pos(x, offsetX), pos(y, offsetY), TILE_SIZE, TILE_SIZE );
			}
		}
	}
}

Renderer::Color MatrixRenderer::getTetrominoColor(MatrixTile tile) {
	switch (tile.type) {
		case TetrominoType::I: return Renderer::Color::CYAN;
		case TetrominoType::O: return Renderer::Color::YELLOW;
		case TetrominoType::T: return Renderer::Color::PURPLE;
		case TetrominoType::S: return Renderer::Color::GREEN;
		case TetrominoType::Z: return Renderer::Color::RED;
		case TetrominoType::J: return Renderer::Color::BLUE;
		case TetrominoType::L: return Renderer::Color::ORANGE;
		default: return Renderer::Color::WHITE;
	}
}

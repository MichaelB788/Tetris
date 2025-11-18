#include "render/matrix-renderer.hpp"

void MatrixRenderer::render(const Matrix& matrix, const Renderer& renderer, const Dimension2D windowDimension) {
	offset.x = (windowDimension.w - pixelDimensions.w) / (2 * tileSize);
	offset.y = (windowDimension.h - pixelDimensions.h) / (2 * tileSize);

	for (int y = 2; y < Matrix::HEIGHT; y++) {
		for (int x = 0; x < Matrix::WIDTH; x++) {
			renderTileAt({x, y}, offset, matrix(x, y), renderer);
		}
	}
}

void MatrixRenderer::renderTileAt(Vector2 pos, Vector2 offset, const MatrixTile& tile, const Renderer& renderer) const {
	Vector2 pixelPos = getPixelPosition(pos, offset);

	if (tile.state == MatrixTile::State::EMPTY) {
		drawTile(renderer, Renderer::Color::GRAY, pixelPos);
	} else if (tile.state == MatrixTile::State::ACTIVE || tile.state == MatrixTile::State::GROUND) {
		drawTile(renderer, getTileColor(tile), pixelPos, true);
		drawTile(renderer, Renderer::Color::BLACK, pixelPos);
	} else {
		drawTile(renderer, Renderer::Color::WHITE, pixelPos);
	}
}

void MatrixRenderer::drawTile(const Renderer& renderer, Renderer::Color color, Vector2 pos, bool filled) const {
	renderer.setSDLRendererColor(color);
	renderer.drawRectangle({pos.x, pos.y, TILE_SIZE, TILE_SIZE}, filled);
}

Renderer::Color MatrixRenderer::getTileColor(MatrixTile tile) const {
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

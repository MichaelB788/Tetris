#include "render/matrix-renderer.hpp"

void MatrixRenderer::render(const Matrix& matrix, const Renderer& renderer, const Window& window) {
	auto [offsetX, offsetY] = window.getWindowSize();

	for (unsigned y = 2; y < Matrix::HEIGHT; y++) {
		for (unsigned x = 0; x < Matrix::WIDTH; x++) {
			renderTileAt(matrix(x, y), renderer, x, y, offsetX, offsetY);
		}
	}
}

void MatrixRenderer::renderTileAt(const MatrixTile& tile, const Renderer& renderer, int x, int y, int offX, int offY) const {
	int px = gridPixel(x, offX);
	int py = gridPixel(y, offY);

	if (tile.state == MatrixTile::State::EMPTY) {
		drawTile(renderer, Renderer::Color::GRAY, px, py);
	} else if (tile.state == MatrixTile::State::ACTIVE || tile.state == MatrixTile::State::GROUND) {
		drawTile(renderer, getTileColor(tile), px, py, true);
		drawTile(renderer, Renderer::Color::BLACK, px, py);
	} else {
		drawTile(renderer, Renderer::Color::WHITE, px, py);
	}
}

void MatrixRenderer::drawTile(const Renderer& renderer, Renderer::Color color, int x, int y, bool filled) const {
	renderer.setSDLRendererColor(color);
	renderer.drawRectangle({x, y, TILE_SIZE, TILE_SIZE}, filled);
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

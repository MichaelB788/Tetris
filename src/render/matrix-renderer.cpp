#include "render/matrix-renderer.hpp"
#include "util/color.hpp"

void MatrixRenderer::render(const Matrix& matrix, const Renderer& renderer, const Dimension2D windowDimension) {
	offset.x = (windowDimension.w - pixelDimensions.w) / (2 * tileSize);
	offset.y = (windowDimension.h - pixelDimensions.h) / (2 * tileSize);

	for (int y = 2; y < Matrix::HEIGHT; y++) {
		for (int x = 0; x < Matrix::WIDTH; x++) {
			renderTileAt({x, y}, matrix(x, y), renderer);
		}
	}
}

void MatrixRenderer::renderTileAt(Vector2 pos, const MatrixTile& tile, const Renderer& renderer) const {
	Vector2 pixelPos = getPixelPosition(pos);
	bool isTetromino = tile.state == MatrixTile::State::ACTIVE || tile.state == MatrixTile::State::GROUND;

	if ( isTetromino ) {
		// Draw the Tetromino block
		renderer.setSDLRendererColor(Color::getTetrominoColor(tile.type));
		renderer.drawRectangle({pixelPos.x, pixelPos.y, tileSize, tileSize}, true);

		// Draw the outline
		renderer.setSDLRendererColor(Color::getColor(Color::ID::BLACK));
		renderer.drawRectangle({pixelPos.x, pixelPos.y, tileSize, tileSize});
	} else {
		renderer.setSDLRendererColor(Color::getMatrixTileColor(tile));
		renderer.drawRectangle({pixelPos.x, pixelPos.y, tileSize, tileSize});
	}
}

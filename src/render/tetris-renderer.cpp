#include "render/tetris-renderer.hpp"

namespace TetrisRenderer::Pixel {
	Vector2 getPosition(Vector2 pos, Vector2 offset) {
		return (pos + offset) * TILE_SIZE;
	}
}

void TetrisRenderer::renderMatrixTileAt(Vector2 pos, Vector2 offset, const Tile& tile, const Renderer& renderer) {
	Vector2 pixelPos = Pixel::getPosition(pos, offset);
	bool isTetromino = tile.state == Tile::State::ACTIVE || tile.state == Tile::State::GROUND;

	if ( isTetromino ) {
		// Draw the Tetromino block
		renderer.setSDLRendererColor(Color::getTetrominoColor(tile.type));
		renderer.drawRectangle({pixelPos.x, pixelPos.y, TILE_SIZE, TILE_SIZE}, true);

		// Draw the outline
		renderer.setSDLRendererColor(Color::getColor(Color::ID::BLACK));
		renderer.drawRectangle({pixelPos.x, pixelPos.y, TILE_SIZE, TILE_SIZE});
	} else {
		renderer.setSDLRendererColor(Color::getMatrixTileColor(tile));
		renderer.drawRectangle({pixelPos.x, pixelPos.y, TILE_SIZE, TILE_SIZE});
	}
}

void TetrisRenderer::renderMatrixAt(Vector2 position, const Matrix& matrix, const Renderer& renderer) {
	for (int y = 2; y < Matrix::HEIGHT; y++) {
		for (int x = 0; x < Matrix::WIDTH; x++) {
			TetrisRenderer::renderMatrixTileAt({x, y}, position, matrix(x, y), renderer);
		}
	}
}

void TetrisRenderer::renderTetrominoAt(Vector2 pos, const Tetromino& tetromino, const Renderer& renderer) {
	for ( const auto& block : tetromino ) {
		// Draw the Tetromino block
		renderer.setSDLRendererColor(Color::getTetrominoColor(tetromino.getType()));
		renderer.drawRectangle(
			{ pos.x + block.x * TILE_SIZE, pos.y + block.y * TILE_SIZE, TILE_SIZE, TILE_SIZE },
			true
		);

		// Draw the outline
		renderer.setSDLRendererColor(Color::getColor(Color::ID::BLACK));
		renderer.drawRectangle(
			{ pos.x + block.x * TILE_SIZE, pos.y + block.y * TILE_SIZE, TILE_SIZE, TILE_SIZE }
		);
	}
}

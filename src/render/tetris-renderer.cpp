#include "render/tetris-renderer.hpp"

void TetrisRenderer::renderMatrixTile(const Tile& tile, const Renderer& renderer, Vector2 pos, Vector2 offset) {
	Vector2 pixelPos = offset + pos * TILE_SIZE;
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

void TetrisRenderer::renderMatrix(const Matrix& matrix, const Renderer& renderer, Vector2 offset) {
	for (int y = 2; y < Matrix::HEIGHT; y++)
		for (int x = 0; x < Matrix::WIDTH; x++)
			renderMatrixTile(matrix(x, y), renderer, {x, y}, offset);
}

void TetrisRenderer::renderTetromino(const Tetromino& tetromino, const Renderer& renderer, Vector2 offset) {
	for ( const auto& block : tetromino ) {
		Vector2 pos = offset + block * TILE_SIZE;

		// Draw the Tetromino block
		renderer.setSDLRendererColor(Color::getTetrominoColor(tetromino.getType()));
		renderer.drawRectangle({ pos.x, pos.y, TILE_SIZE, TILE_SIZE }, true);

		// Draw the outline
		renderer.setSDLRendererColor(Color::getColor(Color::ID::BLACK));
		renderer.drawRectangle({ pos.x, pos.y, TILE_SIZE, TILE_SIZE });
	}
}

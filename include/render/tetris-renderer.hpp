#ifndef TETRIS_RENDERER_H
#define TETRIS_RENDERER_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "util/geometry.hpp"
#include "core/matrix-tile.hpp"
#include "util/renderer.hpp"
#include "util/color.hpp"

namespace TetrisRenderer {
	constexpr int TILE_SIZE = 40;

	constexpr Dimension2D MATRIX_PIXEL_SIZE = { Matrix::WIDTH * TetrisRenderer::TILE_SIZE, Matrix::HEIGHT * TetrisRenderer::TILE_SIZE };

	void renderMatrixTileAt(Vector2 pos, Vector2 offset, const Tile& tile, const Renderer& renderer);

	void renderMatrixAt(Vector2 pos, const Matrix& matrix, const Renderer& renderer);

	void renderTetrominoAt(Vector2 pos, const Tetromino& tetromino, const Renderer& renderer);
}

#endif
